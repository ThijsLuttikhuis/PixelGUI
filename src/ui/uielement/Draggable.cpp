//
// Created by Thijs on 04/04/2023.
//

#include <iostream>
#include "Draggable.h"

void PG::Draggable::onDrag(glm::vec2 relativePos, glm::vec2 dragStartPos) {
    (void) dragStartPos;

    position = glm::round(relativePos - size * 0.5f);
}
