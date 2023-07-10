//
// Created by Thijs on 21/06/2023.
//

#ifndef PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H
#define PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H


#include <utility>


#include "glm/vec2.hpp"
#include "ui/uielement/DraggableButton.h"
#include "ui/uielement/Slider.h"
#include "HelperSprite.h"
#include "Slider.h"
#include "CustomMouse.h"

namespace PG {

class DraggableButtonResizable : public DraggableButton, public CustomMouse {
private:
    bool resizing = false;
    float edgeSize = 4.0f;

    std::shared_ptr<Slider<int>> resizeSlider;



public:
    DraggableButtonResizable() = default;

    DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                             int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), pos, size, keyboardKey) {}

    DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                             std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), pos, size, std::move(sprite), keyboardKey) {}

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onClick(glm::vec2 mousePos) override;

    void onRelease(glm::vec2 mousePos) override;

};

} // PG

#endif //PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H
