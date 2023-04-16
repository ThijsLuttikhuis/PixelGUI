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

class Button : virtual public UIElement {
private:

    void (* callbackFunc)(const std::shared_ptr<UIElement> &button) = emptyCallback;

    static void emptyCallback(const std::shared_ptr<UIElement> &uiElement) {
        (void) uiElement;
        DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Callback:       ", uiElement, " (Empty)");
        throw std::bad_function_call();
    };

public:
    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size, int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, keyboardKey) {}

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size,
           std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey) {}

    void setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &button));

    void onClick(glm::vec2 relativePos) override;

};

}

#endif //PIXELGUI_BUTTON_H
