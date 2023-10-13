//
// Created by Thijs on 22/06/2023.
//

#ifndef PIXELGUI_BUTTONONPRESS_H
#define PIXELGUI_BUTTONONPRESS_H

#include "Button.h"

namespace PG {

class ButtonOnPress : public Button {
public:
    ButtonOnPress() : Button() {};

    ButtonOnPress(std::string name, const glm::vec2 &position, const glm::vec2 &size,
                  int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, keyboardKey) {}

    ButtonOnPress(std::string name, const glm::vec2 &position, const glm::vec2 &size,
                  std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey) {}

    void onClick(glm::vec2 relativePos) override;

};

} // PG

#endif //PIXELGUI_BUTTONONPRESS_H
