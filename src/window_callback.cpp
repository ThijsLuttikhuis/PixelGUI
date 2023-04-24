//
// Created by thijs on 21-12-22.
//

#include <memory>

#include "window/Window.h"


namespace PG {

std::weak_ptr<PG::Window> callback_window_ptr;
std::unique_ptr<glm::vec2> callback_drag_start_position;
std::unique_ptr<bool> callback_left_mouse_button_pressed;

void mouse_position_callback(GLFWwindow* window, double xPos, double yPos) {
    (void) window;

    auto windowPtr = std::shared_ptr<Window>(callback_window_ptr);

    if (*callback_left_mouse_button_pressed) {
        windowPtr->handleMouseDrag(glm::vec2(xPos, yPos), *callback_drag_start_position);
    }
    else {
        windowPtr->handleMousePosition(glm::vec2(xPos, yPos));
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    (void) mods;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (action == GLFW_PRESS) {
            *callback_left_mouse_button_pressed = true;
            *callback_drag_start_position = glm::vec2(xpos, ypos);

            auto windowPtr = std::shared_ptr<Window>(callback_window_ptr);
            windowPtr->handleMouseButton(glm::vec2(xpos, ypos), GLFW_MOUSE_BUTTON_LEFT, false);
        }
        if (action == GLFW_RELEASE) {
            *callback_left_mouse_button_pressed = false;
            *callback_drag_start_position = glm::vec2(0, 0);

            auto windowPtr = std::shared_ptr<Window>(callback_window_ptr);
            windowPtr->handleMouseButton(glm::vec2(xpos, ypos), GLFW_MOUSE_BUTTON_LEFT, true);

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
