//
// Created by thijs on 13-12-22.
//

#ifndef PIXELGUI_WINDOW_H
#define PIXELGUI_WINDOW_H

#include <vector>
#include <ui/UIElement.h>

#include "utilities/DebugPrinter.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace PG {

class Window;

class Game;

class SpriteRenderer;

class TextRenderer;

extern std::weak_ptr<Window> callback_window_ptr;

void mouse_position_callback(GLFWwindow* window, double xPos, double yPos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window : public std::enable_shared_from_this<Window> {

private:

    int xPixels;
    int yPixels;
    GLFWwindow* glfwWindow;

    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;

    std::unique_ptr<std::vector<bool>> keysPressed = std::make_unique<std::vector<bool>>(512, false);

    std::shared_ptr<UIElement> baseUI;
    std::vector<std::shared_ptr<UIElement>> uiElements = {};

    void swapBuffers();

public:
    Window(int xPixels, int yPixels, const std::string &windowTitle = "PixelGUI window");

    ~Window();

    /// functions
    void initialize();

    static void closeWindow();

    /// IO
    void handleMouseButton(double xPos, double yPos) const;

    void handleMousePosition(double xPos, double yPos) const;

    void handleKeyboard(int key, int action, int scanCode);

    /// draw
    void render();

    /// setters
    void setWindowSize(int displayWidth_, int displayHeight_);

    void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    /// getters
    [[nodiscard]] std::shared_ptr<Window> getSharedFromThis();

    [[nodiscard]] int getDisplayWidth() const;

    [[nodiscard]] int getDisplayHeight() const;

    [[nodiscard]] int getXPixels() const;

    [[nodiscard]] int getYPixels() const;

    [[nodiscard]] bool shouldClose() const;
};

}

#endif //PIXELGUI_WINDOW_H
