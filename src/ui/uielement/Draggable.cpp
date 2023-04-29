//
// Created by Thijs on 04/04/2023.
//

#include "Draggable.h"
#include "Scene.h"

namespace PG {

void Draggable::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    (void) dragStartPos;

    position = mousePos - size * 0.5f;
}

}