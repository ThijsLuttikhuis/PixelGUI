//
// Created by Thijs on 27/04/2023.
//

#include "glm/ext.hpp"
#include "RootScene.h"
#include "Slider.h"
#include "EditableValue.h"

namespace PG {

template<typename T>
void Slider<T>::updateSlideOutOfScreen(glm::vec2 &mousePos) {
    (void) mousePos;

    glm::vec2 absoluteMouse = getAbsoluteMousePosition();
    glm::vec2 windowSize = getRootScene()->getSize();
    float insideEdge = 1.0f;
    if (!isPositionInBox(absoluteMouse.x, absoluteMouse.y, glm::vec2(0), windowSize, insideEdge)) {
        auto window = getWindow();

        glm::vec2 newPos = insideEdge + glm::mod(absoluteMouse - insideEdge, windowSize - 2.0f * insideEdge);
        window->forceSetMousePosition(newPos);

        glm::vec2 dragDeltaPos = absoluteMouse - newPos;
        dragDeltaPos *= slideDirection;
        float dValue = (dragDeltaPos.x + dragDeltaPos.y) * slideSpeed;
        dragStartValue += static_cast<T>(dValue);
    }
}

template<>
void Slider<int>::updateSlideOutOfScreen(glm::vec2 &mousePos) {
    (void) mousePos;

    glm::vec2 absoluteMouse = getAbsoluteMousePosition();
    glm::vec2 windowSize = getRootScene()->getSize();
    float insideEdge = 1.0f;
    if (!isPositionInBox(absoluteMouse.x, absoluteMouse.y, glm::vec2(0), windowSize, insideEdge)) {
        auto window = getWindow();

        glm::vec2 newPos = insideEdge + glm::mod(absoluteMouse - insideEdge, windowSize - 2.0f * insideEdge);
        window->forceSetMousePosition(newPos);

        glm::vec2 dragDeltaPos = absoluteMouse - newPos;
        dragDeltaPos *= slideDirection;
        float dValue = (dragDeltaPos.x + dragDeltaPos.y) * slideSpeed;
        dragStartValue += static_cast<int>(dValue);
    }
}

template<typename T>
void Slider<T>::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (oldDragStartPos != dragStartPos) {
        oldDragStartPos = dragStartPos;
        dragStartValue = this->getValue();
    }

    updateSlideOutOfScreen(mousePos);

    glm::vec2 dragDeltaPos = mousePos - dragStartPos;
    dragDeltaPos *= slideDirection;
    double dValue = (dragDeltaPos.x + dragDeltaPos.y) * slideSpeed;
    setValue(static_cast<T>(dragStartValue + dValue));

    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

template<>
void Slider<int>::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (oldDragStartPos != dragStartPos) {
        oldDragStartPos = dragStartPos;
        dragStartValue = this->getValue();
    }

    updateSlideOutOfScreen(mousePos);

    glm::vec2 dragDeltaPos = mousePos - dragStartPos;
    dragDeltaPos *= slideDirection;
    double dValue = (dragDeltaPos.x + dragDeltaPos.y) * slideSpeed;
    setValue(static_cast<int>(dragStartValue + dValue));

    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

template<typename T>
void Slider<T>::setSlideDirection(glm::vec2 slideDirection_) {
    slideDirection = slideDirection_;
}

template<typename T>
glm::vec2 Slider<T>::getSlideDirection() const {
    return slideDirection;
}

template<>
void Slider<int>::setSlideDirection(glm::vec2 slideDirection_) {
    slideDirection = slideDirection_;
}

template<>
glm::vec2 Slider<int>::getSlideDirection() const {
    return slideDirection;
}

} // PG
