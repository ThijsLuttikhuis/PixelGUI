//
// Created by thijs on 21-12-22.
//

#include <memory>
#include "window/Window.h"
#include "game/Game.h"

namespace PG {

std::weak_ptr<Window> callback_window_ptr;

void mouse_position_callback(GLFWwindow* window, double xPos, double yPos) {
    (void) window;

    auto windowPtr = std::shared_ptr<Window>(callback_window_ptr);
    windowPtr->handleMousePosition(xPos, yPos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    (void) mods;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (action == GLFW_RELEASE) {
            auto windowPtr = std::shared_ptr<Window>(callback_window_ptr);
            windowPtr->handleMouseButton(xpos, ypos);
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    (void) window, (void) mode;

    auto windowPtr = std::shared_ptr<Window>(callback_window_ptr);
    windowPtr->handleKeyboard(key, action, scancode);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void) window;

    glViewport(0, 0, width, height);
}

}
