//
// Created by Thijs on 04/04/2023.
//

#include "DraggableButton.h"

namespace PG {

void DraggableButton::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    // do both onDrags
    Draggable::onDrag(mousePos, dragStartPos);
    ButtonOnRelease::onDrag(mousePos, dragStartPos);
}

}
