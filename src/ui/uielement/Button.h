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
public:
    enum pressMode {
        pressOnClick,
        pressOnRelease,
        pressOnReleaseAfterDrag,
        isDraggingForPressOnReleaseAfterDrag
    };
private:

    pressMode pressMode = pressOnReleaseAfterDrag;

    void (* callbackFunc)(const std::shared_ptr<UIElement> &button) = emptyCallback;


    static void emptyCallback(const std::shared_ptr<UIElement> &uiElement) {
        (void) uiElement;
        DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Callback:       ", uiElement, " (Empty)");
        throw std::bad_function_call();
    };

public:
    Button() : UIElement() {};

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size,
           int keyboardKey = GLFW_KEY_UNKNOWN, enum pressMode pressMode = pressOnReleaseAfterDrag)
          : UIElement(std::move(name), position, size, keyboardKey), pressMode(pressMode) {}

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
           int keyboardKey = GLFW_KEY_UNKNOWN, enum pressMode pressMode = pressOnReleaseAfterDrag)
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey),
            pressMode(pressMode) {}

    void setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &button));

    void setPressMode(enum pressMode pressMode);

    void onClick(glm::vec2 relativePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onRelease(glm::vec2 mousePos) override;
};

}

#endif //PIXELGUI_BUTTON_H
