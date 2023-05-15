//
// Created by Thijs on 27/04/2023.
//

#ifndef PIXELGUI_SLIDER_H
#define PIXELGUI_SLIDER_H

#include <functional>
#include "UIElement.h"
#include "Callbackable.h"

namespace PG {

class Slider : virtual public UIElement, virtual public Callbackable {
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
    double slideSpeed = 0.05;

public:
    Slider() : UIElement() {};

    Slider(std::string name, const glm::vec2 &position, const glm::vec2 &size,
    int keyboardKey = GLFW_KEY_UNKNOWN, enum slideMode slideMode = horizontalOnDrag)
    : UIElement(std::move(name), position, size, keyboardKey), slideMode(slideMode) {}

    Slider(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
    int keyboardKey = GLFW_KEY_UNKNOWN, enum slideMode slideMode = horizontalOnDrag)
    : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey),
      slideMode(slideMode) {}

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    /// Set value of the slider.
    void setValue(int value_);

    /// Set mode of the slider (e.g. horizontalOnDrag, verticalOnDrag).
    void setSlideMode(enum slideMode slideMode);

    /// Get value of the slider.
    [[nodiscard]] int getValue() const;

    /// Get mode of the slider.
    [[nodiscard]] enum slideMode getSlideMode() const;

    void updateSlideOutOfScreen(glm::vec2 mousePos);
};

}

#endif //PIXELGUI_SLIDER_H
