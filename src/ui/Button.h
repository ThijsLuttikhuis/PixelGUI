//
// Created by thijs on 5-1-23.
//

#ifndef PIXELGUI_BUTTON_H
#define PIXELGUI_BUTTON_H

#include <functional>
#include "UIElement.h"
#include "GLFW/glfw3.h"
#include "utilities/DebugPrinter.h"

namespace PG {

class Button : public UIElement {
private:

    void (*callbackFunc)() = emptyCallback;

    static void emptyCallback() {
        DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Callback:       Empty");
        throw std::bad_function_call();
    };
public:
    Button(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
           int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), pos, size, keyboardKey) {}

    Button(std::string name, const glm::vec2 &pos, const glm::vec2 &size, std::unique_ptr<Sprite> sprite, int keyboardKey = -1)
          : UIElement(std::move(name), pos, size, std::move(sprite), keyboardKey) {}

    void setCallbackFunction(void (*func)());

    void onClick(glm::vec2 relativePos) override;
};

}

#endif //PIXELGUI_BUTTON_H
