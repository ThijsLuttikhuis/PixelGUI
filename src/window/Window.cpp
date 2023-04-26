//
// Created by thijs on 13-12-22.
//

#include <iostream>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

#include "window/render/TextRenderer.h"
#include "window/render/SpriteRenderer.h"

#include "Window.h"

namespace PG {

std::shared_ptr<Window> Window::getSharedFromThis() {
    return shared_from_this();
}

Window::Window(int xPixels, int yPixels, const std::string &windowTitle)
      : xPixels(xPixels), yPixels(yPixels),
        baseUI(std::make_shared<Scene>(windowTitle,
                                       glm::vec2(0.0f),
                                       glm::vec2(xPixels, yPixels))) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindow = glfwCreateWindow(xPixels, yPixels, windowTitle.c_str(), nullptr, nullptr);
    if (glfwWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowAspectRatio(glfwWindow, xPixels, yPixels);
    glfwSetWindowSizeLimits(glfwWindow, xPixels, yPixels, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(glfwWindow);

    // set callbacks
    glfwSetKeyCallback(glfwWindow, key_callback);
    glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
    glfwSetCursorPosCallback(glfwWindow, mouse_position_callback);
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glViewport(0, 0, xPixels, yPixels);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_ALPHA_TEST);

    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0);
}

Window::~Window() {
    glfwTerminate();
}

void Window::initialize() {
    callback_window_ptr = getSharedFromThis();
    callback_left_mouse_button_pressed = std::make_unique<bool>(false);
    callback_drag_start_position = std::make_unique<glm::vec2>(0, 0);

    auto shader = std::make_shared<Shader>();
    std::string vertexFile = "../assets/shaders/sprite.vs";
    std::string fragmentFile = "../assets/shaders/sprite.fs";
    std::string spriteFolder = "../assets/sprites/";
    std::string textFolder = "../assets/sprites/textsprites";

    shader->compile(vertexFile, fragmentFile);

    glm::mat4 projection = glm::ortho(0.0f, (float) getDisplayWidth(), (float) getDisplayHeight(),
                                      0.0f, -1.0f, 1.0f);

    spriteRenderer = std::make_unique<SpriteRenderer>(shader, projection);
    spriteRenderer->addAllTexturesInDir(spriteFolder);

    textRenderer = std::make_unique<TextRenderer>(shader, projection);
    textRenderer->setTexture(textFolder);
}

void Window::render() {

    glfwPollEvents();

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    spriteRenderer->setBaseUI(baseUI);
    textRenderer->setBaseUI(baseUI);

    baseUI->draw(spriteRenderer, textRenderer);

    swapBuffers();
}

void Window::swapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::closeWindow() {
    auto glfwWindow = std::shared_ptr<Window>(callback_window_ptr)->glfwWindow;
    glfwSetWindowShouldClose(glfwWindow, true);
}

void Window::handleMouseButton(glm::vec2 pos, int buttonID, bool isRelease) const {
    (void) buttonID;
    //TODO: buttonID = left/right/3rd/nth mouse button

    pos *= glm::vec2((double) xPixels / getDisplayWidth(), (double) yPixels / getDisplayHeight());

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_ALWAYS, "mouse click:    ", pos.x, ", ", pos.y);

    if (isRelease) {
        baseUI->onRelease(pos);
    }
    else {
        baseUI->onClick(pos);
    }
}

void Window::handleMousePosition(glm::vec2 pos) const {
    pos *= glm::vec2((double) xPixels / getDisplayWidth(), (double) yPixels / getDisplayHeight());

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_POSITION_ALWAYS, "mouse position: ", pos.x, ", ", pos.y);

    baseUI->onHover(pos);
}

void Window::handleMouseDrag(glm::vec2 pos, glm::vec2 dragStartPos) const {
    pos *= glm::vec2((double) xPixels / getDisplayWidth(), (double) yPixels / getDisplayHeight());
    dragStartPos *= glm::vec2((double) xPixels / getDisplayWidth(), (double) yPixels / getDisplayHeight());

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_POSITION_ALWAYS,
                        "mouse drag:     ", dragStartPos.x, " ", pos.x, ", ", dragStartPos.y, " ", pos.y);

    baseUI->onDrag(pos, dragStartPos);
}

void Window::handleKeyboard(int key, int action, int scanCode) {
    (void) scanCode;

    if (key == GLFW_KEY_F4 && action == GLFW_PRESS && keysPressed->at(GLFW_KEY_LEFT_ALT)) {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keysPressed->at(key) = true;

            auto keyName = glfwGetKeyName(key, scanCode);
            DebugPrinter::print(DebugPrinter::DEBUG_KEYBOARD_KEYS, "press key:     ", (keyName ? keyName : "UNKNOWN"));
        } else if (action == GLFW_RELEASE) {
            keysPressed->at(key) = false;

            auto keyName = glfwGetKeyName(key, scanCode);
            DebugPrinter::print(DebugPrinter::DEBUG_KEYBOARD_KEYS, "release key:   ", (keyName ? keyName : "UNKNOWN"));
        }
    }
}

void Window::setWindowSize(int displayWidth_, int displayHeight_) {
    double aspectRatio = (double) xPixels / yPixels;
    double newAspectRatio = (double) displayWidth_ / displayHeight_;

    if (newAspectRatio > aspectRatio) {
        displayWidth_ = static_cast<int>(aspectRatio * displayHeight_);
    } else if (newAspectRatio < aspectRatio) {
        displayHeight_ = static_cast<int>(1.0 / aspectRatio * displayWidth_);
    }

    glfwSetWindowSize(glfwWindow, displayWidth_, displayHeight_);
}

int Window::getDisplayWidth() const {
    int width;
    int height;
    glfwGetWindowSize(glfwWindow, &width, &height);
    return width;
}

int Window::getDisplayHeight() const {
    int width;
    int height;
    glfwGetWindowSize(glfwWindow, &width, &height);
    return height;
}

int Window::getXPixels() const {
    return xPixels;
}

int Window::getYPixels() const {
    return yPixels;
}

void Window::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    baseUI->addUIElement(uiElement);
}

}
