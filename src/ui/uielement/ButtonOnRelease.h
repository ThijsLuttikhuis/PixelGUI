//
// Created by Thijs on 22/06/2023.
//

#ifndef PIXELGUI_BUTTONONRELEASE_H
#define PIXELGUI_BUTTONONRELEASE_H

#include "Button.h"

namespace PG {

class ButtonOnRelease : public Button {
public:
    ButtonOnRelease() : Button() {};

    ButtonOnRelease(std::string name, const glm::vec2 &position, const glm::vec2 &size,
                    int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, keyboardKey) {}

    ButtonOnRelease(std::string name, const glm::vec2 &position, const glm::vec2 &size,
                    std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey) {}

protected:
    bool pressed = false;
    bool dragging = false;

public:
    void onClick(glm::vec2 relativePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onRelease(glm::vec2 mousePos) override;

};

} // PG

#endif //PIXELGUI_BUTTONONRELEASE_H
