//
// Created by Thijs on 27/04/2023.
//

#include "RootScene.h"
#include "Slider.h"

namespace PG {

void Slider::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (oldDragStartPos != dragStartPos) {
        oldDragStartPos = dragStartPos;
        dragStartValue = value;
        std::cout <<"CHANGED";
    }

    updateSlideOutOfScreen(mousePos);

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

    DebugPrinter::print(DebugPrinter::ALL, "slider value: ", value, "; dragDeltaPos: ", dragDeltaPos.x, "; mousePos: ", mousePos.x);


    std::cout << dragStartValue << "     \n";
    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Slider::updateSlideOutOfScreen(glm::vec2 mousePos) {
    (void) mousePos;

    auto absoluteMouse = getAbsoluteMousePosition();
    auto windowSize = getRootScene()->getSize();
    float insideEdge = 2.0f;
    if (!isPositionInBox(absoluteMouse.x, absoluteMouse.y, glm::vec2(0), windowSize, insideEdge)) {
        auto window = getWindow();
        auto newPos = glm::mod(absoluteMouse, (glm::vec2)windowSize - glm::vec2(2.0f * insideEdge));
        window->forceSetMousePosition(newPos);
        switch (slideMode) {
            case Slider::horizontalOnDrag:
                dragStartValue = dragStartValue + (int)((absoluteMouse.x - newPos.x) * slideSpeed);
                break;
            case Slider::verticalOnDrag:
                dragStartValue = dragStartValue + (int)((absoluteMouse.y - newPos.y) * slideSpeed);
                break;
            default:
                throw std::exception();
        }
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