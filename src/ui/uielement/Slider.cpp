//
// Created by Thijs on 27/04/2023.
//

#include "Slider.h"

namespace PG {

void Slider::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    dragDeltaPos = mousePos - dragStartPos;
    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Slider::setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &)) {
    callbackFunc = func;
}

void Slider::setSlideMode(enum Slider::slideMode slideMode_) {
    slideMode = slideMode_;
}

glm::vec2 Slider::getDragDeltaPos() {
    return dragDeltaPos;
}

enum Slider::slideMode Slider::getSlideMode() {
    return slideMode;
}

}