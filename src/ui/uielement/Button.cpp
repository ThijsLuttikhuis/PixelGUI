//
// Created by thijs on 5-1-23.
//

#include "Button.h"
#include "DraggableButton.h"

namespace PG {

void Button::onClick(glm::vec2 relativePos) {
    UIElement::onClick(relativePos);
    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

void Button::setCallbackFunction(void (*func)(const std::shared_ptr<UIElement> &button)) {
    callbackFunc = func;
}

}
