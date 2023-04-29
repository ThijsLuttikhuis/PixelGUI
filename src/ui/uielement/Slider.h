//
// Created by Thijs on 27/04/2023.
//

#ifndef PIXELGUI_SLIDER_H
#define PIXELGUI_SLIDER_H

#include <functional>
#include "UIElement.h"

namespace PG {

class Slider : virtual public UIElement {
public:
    enum slideMode {
        horizontalOnDrag,
        verticalOnDrag
    };
private:

    slideMode slideMode = horizontalOnDrag;
    glm::vec2 oldDragStartPos = glm::vec2{};
    int dragStartValue = 50;

    int value = 50;
    int minValue = 0;
    int maxValue = 100;
    double slideSpeed = 0.4;

    void (* callbackFunc)(const std::shared_ptr<UIElement> &button) = emptyCallback;

    static void emptyCallback(const std::shared_ptr<UIElement> &uiElement) {
        (void) uiElement;
        DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Callback:       ", uiElement, " (Empty)");
        throw std::bad_function_call();
    };

public:
    Slider() : UIElement() {};

    Slider(std::string name, const glm::vec2 &position, const glm::vec2 &size,
    int keyboardKey = GLFW_KEY_UNKNOWN, enum slideMode slideMode = horizontalOnDrag)
    : UIElement(std::move(name), position, size, keyboardKey), slideMode(slideMode) {}

    Slider(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
    int keyboardKey = GLFW_KEY_UNKNOWN, enum slideMode slideMode = horizontalOnDrag)
    : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey),
      slideMode(slideMode) {}

    void setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &slider));

    void setSlideMode(enum slideMode slideMode);

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    [[nodiscard]] int getValue();

    [[nodiscard]] enum slideMode getSlideMode();

};

}

#endif //PIXELGUI_SLIDER_H
