//
// Created by Thijs on 21/06/2023.
//

#include "DraggableButtonResizable.h"

namespace PG {

void DraggableButtonResizable::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (resizing) {
        dragging = true;

        // resize
        glm::vec2 diff = mousePos - dragStartPos;
        size += diff;
        if (size.x < 1) {
            size.x = 1;
        }
        if (size.y < 1) {
            size.y = 1;
        }
    } else {
        DraggableButton::onDrag(mousePos, dragStartPos);
    }
}

void DraggableButtonResizable::onRelease(glm::vec2 mousePos) {

    if (!dragging) {
        // if mouse is on the edge of the button, switch to resizing mode
        resizing = isMouseHovering(mousePos) && !isPositionInBox(mousePos.x, mousePos.y, edgeSize);
    } else {
        try {
            callbackFunc(getSharedFromThis());
        }
        catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
    }
}

void DraggableButtonResizable::onClick(glm::vec2 mousePos) {
    (void) mousePos;

    pressed = true;
    dragging = false;
}

} // PG
