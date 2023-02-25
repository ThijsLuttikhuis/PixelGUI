//
// Created by thijs on 13-12-22.
//

#include <iostream>
#include <memory>
#include "Window.h"
#include "game/Game.h"

namespace PG {

std::shared_ptr<Window> Window::getSharedFromThis() {
    return shared_from_this();
}

Window::Window(int xPixels, int yPixels, double scale, const std::string &windowTitle) :
      xPixels(xPixels), yPixels(yPixels) {

    int displayWidth = (int) (scale * xPixels);
    int displayHeight = (int) (scale * yPixels);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindow = glfwCreateWindow(displayWidth, displayHeight, windowTitle.c_str(), nullptr, nullptr);
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

    glfwSetWindowSize(glfwWindow, displayWidth, displayHeight);



    glViewport(0, 0, displayWidth, displayHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_ALPHA_TEST);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0);

}

Window::~Window() {
    glfwTerminate();
}

void Window::initialize() {
    callback_window_ptr = getSharedFromThis();
}

void Window::render() {
    glClearColor(0.25f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto gamePtr = std::shared_ptr<Game>(game);
    gamePtr->render();

    swapBuffers();
    glfwPollEvents();
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

void Window::handleMouseButton(double xPos, double yPos) {
    xPos *= (double) xPixels / getDisplayWidth();
    yPos *= (double) yPixels / getDisplayHeight();

    auto gamePtr = std::shared_ptr<Game>(game);

    gamePtr->handleMouseButton(xPos, yPos);
}

void Window::handleMousePosition(double xPos, double yPos) {
    xPos *= (double) xPixels / getDisplayWidth();
    yPos *= (double) yPixels / getDisplayHeight();

    auto gamePtr = std::shared_ptr<Game>(game);

    gamePtr->handleMousePosition(xPos, yPos);
}

void Window::handleKeyboard(int key, int action, int scanCode) {
    (void) scanCode;

    if (key == GLFW_KEY_F4 && action == GLFW_PRESS && keysPressed->at(GLFW_KEY_LEFT_ALT)) {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    std::cout << key << std::endl;

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keysPressed->at(key) = true;
        } else if (action == GLFW_RELEASE) {
            keysPressed->at(key) = false;
        }
    }

    auto gamePtr = std::shared_ptr<Game>(game);
    gamePtr->handleKeyboard(key, action, keysPressed);
}

void Window::setWindowSize(int displayWidth_, int displayHeight_) {
    double aspectRatio = (double)xPixels / yPixels;

    double newAspectRatio = (double)displayWidth_ / displayHeight_;

    if (newAspectRatio > aspectRatio) {
        displayWidth_ = static_cast<int>(aspectRatio * displayHeight_);
    }
    else {
        displayHeight_ = static_cast<int>(1.0 / aspectRatio * displayWidth_);
    }

    glfwSetWindowSize(glfwWindow, displayWidth_, displayHeight_);
}

void Window::setGame(const std::weak_ptr<Game> &game_) {
    game = game_;
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

}