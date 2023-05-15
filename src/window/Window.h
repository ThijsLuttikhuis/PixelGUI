//
// Created by thijs on 13-12-22.
//

#ifndef PIXELGUI_WINDOW_H
#define PIXELGUI_WINDOW_H

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ui/uielement/UIElement.h"
#include "ui/uielement/Scene.h"
#include "utilities/DebugPrinter.h"

namespace PG {

class Window;

class RootScene;

class SpriteRenderer;

class TextRenderer;

extern std::weak_ptr<Window> callback_window_ptr;
extern std::unique_ptr<glm::vec2> callback_drag_start_position;
extern std::unique_ptr<bool> callback_left_mouse_button_pressed;

void mouse_position_callback(GLFWwindow* window, double xPos, double yPos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window : public std::enable_shared_from_this<Window> {

private:
    int xPixels;
    int yPixels;
    GLFWwindow* glfwWindow;
    std::string title;

    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;

    std::unique_ptr<std::vector<bool>> keysPressed = std::make_unique<std::vector<bool>>(512, false);

    std::shared_ptr<RootScene> rootScene;

    void swapBuffers();

public:
    Window(int xPixels, int yPixels, const std::string &windowTitle = "PixelGUI window");

    ~Window();

    void initialize();

    static void closeWindow();

    void handleMouseButton(glm::vec2 pos, int buttonID, bool isRelease) const;

    void handleMouseDrag(glm::vec2 pos, glm::vec2 dPos) const;

    void handleMousePosition(glm::vec2 pos) const;

    void forceSetMousePosition(glm::vec2 pos) const;

    void handleKeyboard(int key, int action, int scanCode);

    void render();

    void setWindowSize(int displayWidth_, int displayHeight_);

    void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    [[nodiscard]] std::shared_ptr<Window> getSharedFromThis();

    [[nodiscard]] int getDisplayWidth() const;

    [[nodiscard]] int getDisplayHeight() const;

    [[nodiscard]] int getXPixels() const;

    [[nodiscard]] int getYPixels() const;

    [[nodiscard]] glm::vec2 getMousePosition() const;

    [[nodiscard]] bool shouldClose() const;
};

}

#endif //PIXELGUI_WINDOW_H
