//
// Created by Thijs on 27/04/2023.
//

#include "RootScene.h"
#include "Slider.h"
#include "EditableValue.h"

namespace PG {

template<typename T>
void Slider<T>::updateSlideOutOfScreen(glm::vec2 mousePos) {
    (void) mousePos;

//    auto absoluteMouse = getAbsoluteMousePosition();
//    auto windowSize = getRootScene()->getSize();
//    float insideEdge = 2.0f;
//    if (!isPositionInBox(absoluteMouse.x, absoluteMouse.y, glm::vec2(0), windowSize, insideEdge)) {
//        auto window = getWindow();
//        auto newPos = glm::mod(absoluteMouse, (glm::vec2) windowSize - glm::vec2(2.0f * insideEdge));
//        window->forceSetMousePosition(newPos);
//        dragStartValue = dragStartValue + (int) ((absoluteMouse.x - newPos.x) * slideSpeed);
//
//    }
}

template<>
void Slider<int>::updateSlideOutOfScreen(glm::vec2 mousePos) {
    (void) mousePos;
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

    DebugPrinter::print(DebugPrinter::ALL, "slider value: ", this->value, "; dragDeltaPos: ", dragDeltaPos.x,
                        "; mousePos: ", mousePos.x);

    std::cout << dragStartValue << "     \n";
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

    DebugPrinter::print(DebugPrinter::ALL, "slider value: ", this->getValue(), "; dragDeltaPos: ",
                        dragDeltaPos.x, "; mousePos: ", mousePos.x);

    std::cout << dragStartValue << "     \n";
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
