//
// Created by Thijs on 27/04/2023.
//

#ifndef PIXELGUI_SLIDER_H
#define PIXELGUI_SLIDER_H

#include <functional>
#include "UIElement.h"
#include "Callbackable.h"
#include "EditableValue.h"

namespace PG {

template<typename T>
class Slider : public UIElement, public EditableValue<T>, public Callbackable {
public:
    static glm::vec2 horizontalOnDrag() { return {1.0f, 0.0f}; }

    static glm::vec2 verticalOnDrag() { return {0.0f, 1.0f}; }

private:
    glm::vec2 slideDirection;
    glm::vec2 oldDragStartPos = glm::vec2{};
    T dragStartValue;
    float slideSpeed = 0.05;

public:
    Slider() = default;

    Slider(std::string name, const glm::vec2 &position, const glm::vec2 &size,
           const T &value, const T &minValue, const T &maxValue, const T &dragStartValue, float slideSpeed = 0.05,
           int keyboardKey = GLFW_KEY_UNKNOWN, glm::vec2 slideMode = Slider::horizontalOnDrag())
          : UIElement(std::move(name), position, size, keyboardKey),
            EditableValue<T>(value, minValue, maxValue),
            slideDirection(slideMode), dragStartValue(dragStartValue), slideSpeed(slideSpeed) {}

    Slider(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
           const T &value, const T &minValue, const T &maxValue, const T &dragStartValue, float slideSpeed = 0.05,
           int keyboardKey = GLFW_KEY_UNKNOWN, glm::vec2 slideMode = Slider::horizontalOnDrag())
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey),
            EditableValue<T>(value, minValue, maxValue),
            slideDirection(slideMode), dragStartValue(dragStartValue), slideSpeed(slideSpeed) {}

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    /// Set mode of the slider (e.g. horizontalOnDrag(), verticalOnDrag()).
    void setSlideDirection(glm::vec2 slideDirection_);

    /// Get mode of the slider.
    [[nodiscard]] glm::vec2 getSlideDirection() const;

    /// Update cursor when sliding out of the window.
    void updateSlideOutOfScreen(glm::vec2 &mousePos);
};

}

#endif //PIXELGUI_SLIDER_H
