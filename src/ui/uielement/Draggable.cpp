//
// Created by Thijs on 04/04/2023.
//

#include "Draggable.h"
#include "Scene.h"

namespace PG {

void Draggable::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    (void) dragStartPos;

    position = mousePos - size * 0.5f;

    auto parent = std::shared_ptr<Scene>(parentPtr);
    if (!parent->getChangeOwnerWhenDraggingOutsideScene() ||
        isPositionInBox(position.x, position.y, parent->getPosition(), parent->getSize())) {

        return;
    }

    // allow change owner and position is outside the box -> then change owner

    auto parentSiblings = parent->getSiblings();
    for (auto &parentSibUIElement: parentSiblings) {
        auto parentSibScene = std::dynamic_pointer_cast<Scene>(parentSibUIElement);
        if (!parentSibScene) {
            continue;
        }

        glm::vec2 parentSibPos = parentSibScene->getPosition() - parent->getPosition();
        if (isPositionInBox(position.x, position.y, parentSibPos, parentSibScene->getSize())) {

            bool ownerChanged = parent->changeOwner(getSharedFromThis(), parentSibScene);
            if (!ownerChanged) {
                throw std::exception();
            }

            return;
        }

    }

}

}