//
// Created by thijs on 13-12-22.
//

#ifndef PIXELGUI_WINDOW_H
#define PIXELGUI_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

namespace PG {

class Game;

class Window : public std::enable_shared_from_this<Window> {
private:
    int xPixels;
    int yPixels;

    GLFWwindow* glfwWindow;

    std::unique_ptr<std::vector<bool>> keysPressed = std::make_unique<std::vector<bool>>(512, false);

    std::weak_ptr<Game> game;

    void swapBuffers();

public:
    Window(int xPixels, int yPixels, double scale = 2.0, const std::string &windowTitle = "PixelGUI window");

    ~Window();

    /// functions
    void initialize();

    static void closeWindow();

    /// IO
    void handleMouseButton(double xPos, double yPos);

    void handleMousePosition(double xPos, double yPos);

    void handleKeyboard(int key, int action, int scanCode);

    /// draw
    void render();

    /// setters
    void setWindowSize(int displayWidth_, int displayHeight_);

    void setGame(const std::weak_ptr<Game> &game_);

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
