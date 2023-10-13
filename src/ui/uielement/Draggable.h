//
// Created by Thijs on 04/04/2023.
//

#ifndef PIXELGUI_DRAGGABLE_H
#define PIXELGUI_DRAGGABLE_H

#include "UIElement.h"

namespace PG {

class Draggable : virtual public UIElement {
public:
    Draggable() = default;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

};

}

#endif //PIXELGUI_DRAGGABLE_H
