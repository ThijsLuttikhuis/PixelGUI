//
// Created by thijs on 5-1-23.
//

#ifndef PIXELGUI_BUTTON_H
#define PIXELGUI_BUTTON_H

#include "UIElement.h"

namespace PG {

class Button : public UIElement {
private:
    int keyboardKey;

    bool enabled = true;

    bool ActivateOnRelease = true;

public:
    Button(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
           int keyboardKey)
          : UIElement(std::move(name), pos, size), keyboardKey(keyboardKey) {}

    Button(std::string name, const glm::vec2 &pos, const glm::vec2 &size, std::unique_ptr<Sprite> sprite, int keyboardKey = -1)
          : UIElement(std::move(name), pos, size, std::move(sprite)), keyboardKey(keyboardKey) {}

    [[nodiscard]] bool isPressed(double xPos, double yPos) const;

    [[nodiscard]] bool isKeyPressed(int key) const;

    [[nodiscard]] bool isEnabled() const;

    void setEnabled(bool enabled_);

};

}

#endif //PIXELGUI_BUTTON_H
