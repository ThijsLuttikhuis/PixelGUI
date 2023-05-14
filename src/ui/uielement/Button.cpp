//
// Created by thijs on 5-1-23.
//

#include "Button.h"

namespace PG {

void Button::onClick(glm::vec2 mousePos) {
    UIElement::onClick(mousePos);
    if (pressMode == pressOnClick) {
        try {
            callbackFunc(getSharedFromThis());
        }
        catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
    } else if (pressMode == pressOnReleaseAfterDrag) {
        pressMode = isDraggingForPressOnReleaseAfterDrag;
    }
}

void Button::onRelease(glm::vec2 mousePos) {
    UIElement::onRelease(mousePos);
    if (pressMode == pressOnRelease || pressMode == isDraggingForPressOnReleaseAfterDrag) {
        pressMode = (pressMode == isDraggingForPressOnReleaseAfterDrag) ? pressOnReleaseAfterDrag : pressMode;
        try {
            callbackFunc(getSharedFromThis());
        }
        catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
    }
}

void Button::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    (void) dragStartPos;

    if (pressMode == isDraggingForPressOnReleaseAfterDrag && !isMouseHovering(mousePos)) {
        pressMode = pressOnReleaseAfterDrag;
    }
}

void Button::setPressMode(enum Button::pressMode pressMode_) {
    pressMode = pressMode_;
}

enum Button::pressMode Button::getPressMode() {
    return pressMode;
}

}
