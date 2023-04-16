//
// Created by Thijs on 04/04/2023.
//

#ifndef PIXELGUI_DRAGGABLEBUTTON_H
#define PIXELGUI_DRAGGABLEBUTTON_H

#include "Draggable.h"
#include "Button.h"

namespace PG {

class DraggableButton : public Draggable, public Button {
private:

public:
    DraggableButton(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                    int keyboardKey = GLFW_KEY_UNKNOWN)
          : Button(std::move(name), pos, size, keyboardKey) {}

    DraggableButton(std::string name, const glm::vec2 &pos, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
                    int keyboardKey = GLFW_KEY_UNKNOWN)
          : Button(std::move(name), pos, size, std::move(sprite), keyboardKey) {}

};

}

#endif //PIXELGUI_DRAGGABLEBUTTON_H
