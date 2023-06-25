//
// Created by Thijs on 22/06/2023.
//

#include "ButtonOnRelease.h"

namespace PG {

void ButtonOnRelease::onClick(glm::vec2 mousePos) {
    (void) mousePos;

    pressed = true;
}

void ButtonOnRelease::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    (void) dragStartPos;

    dragging = true;
    if (!isMouseHovering(mousePos)) {
        pressed = false;
    }
}

void ButtonOnRelease::onRelease(glm::vec2 mousePos) {
    (void) mousePos;

    dragging = false;
    if (pressed) {
        try {
            callbackFunc(getSharedFromThis());
        }
        catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
        pressed = false;
    }
}

} // PG
