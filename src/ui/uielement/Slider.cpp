//
// Created by Thijs on 27/04/2023.
//

#include "Slider.h"

namespace PG {

void Slider::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (oldDragStartPos != dragStartPos) {
        oldDragStartPos = dragStartPos;
        dragStartValue = value;
    }
    glm::vec2 dragDeltaPos = mousePos - dragStartPos;

    switch (slideMode) {
        case Slider::horizontalOnDrag:
            value = dragStartValue + static_cast<int>(dragDeltaPos.x * slideSpeed);
            break;
        case Slider::verticalOnDrag:
            value = dragStartValue + static_cast<int>(dragDeltaPos.y * slideSpeed);
            break;
        default:
            throw std::exception();
    }
    value = std::clamp(value, minValue, maxValue);
    DebugPrinter::print(DebugPrinter::ALL, "slider value: ", value, "  ", dragDeltaPos.x, " ", mousePos.x);

    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Slider::setSlideMode(enum Slider::slideMode slideMode_) {
    slideMode = slideMode_;
}

int Slider::getValue() const {
    return value;
}

enum Slider::slideMode Slider::getSlideMode() const {
    return slideMode;
}

void Slider::setValue(int value_) {
    value = value_;
}

}