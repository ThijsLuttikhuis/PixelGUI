//
// Created by Thijs on 21/06/2023.
//

#include "DraggableButtonResizable.h"

namespace PG {

void DraggableButtonResizable::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (this->resizing) {
        this->dragging = true;

        Slider<int>::onDrag(mousePos, dragStartPos);


    } else {
        DraggableButton::onDrag(mousePos, dragStartPos);
    }
}

void DraggableButtonResizable::onRelease(glm::vec2 mousePos) {

    if (!dragging) {
        // if mouse is on the edge of the button, switch to resizing mode
        resizing = isPositionOnEdge(mousePos);
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

void DraggableButtonResizable::onHover(glm::vec2 mousePos) {
    if (resizing) {
        if (isPositionOnEdge(mousePos)) {
            customMouse->setMouse();
        }
    }
}

bool DraggableButtonResizable::isPositionOnEdge(glm::vec2 mousePos) {
    return isMouseHovering(mousePos) && !isPositionInBox(mousePos.x, mousePos.y, edgeSize);
}

std::shared_ptr<CustomMouseSprite> &DraggableButtonResizable::getCustomMouse() {
    return customMouse;
}

void DraggableButtonResizable::setParent(std::weak_ptr<Scene> parent_) {
    UIElement::setParent(parent_);
    if (customMouse) {
        customMouse->setRootScene(getRootScene());
    }
}

void DraggableButtonResizable::setCustomMouse(const std::shared_ptr<CustomMouseSprite> &customMouse_) {
    customMouse = customMouse_;
    if (hasParent()) {
        customMouse->setRootScene(getRootScene());
    }
}

} // PG
