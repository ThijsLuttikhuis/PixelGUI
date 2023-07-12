//
// Created by thijs on 5-1-23.
//

#ifndef PIXELGUI_BUTTON_H
#define PIXELGUI_BUTTON_H

#include <functional>

#include "utilities/DebugPrinter.h"
#include "Callbackable.h"
#include "UIElement.h"

namespace PG {

class Button : virtual public UIElement, virtual public Callbackable {
public:
    Button() = default;

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size, int keyboardKey = GLFW_KEY_UNKNOWN)
    : UIElement(std::move(name), position, size, keyboardKey) {}

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
    : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey) {}
};

} // PG

#endif //PIXELGUI_BUTTON_H
