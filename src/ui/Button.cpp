//
// Created by thijs on 5-1-23.
//

#include "Button.h"

namespace PG {

bool Button::isPressed(double xPos, double yPos) const {
    return enabled && isMouseHovering(xPos, yPos);
}

bool Button::isKeyPressed(int key) const {
    return enabled && (key == keyboardKey);
}

bool Button::isEnabled() const {
    return enabled;
}

void Button::setEnabled(bool enabled_) {
    enabled = enabled_;
}

void Button::onClick(glm::vec2 relativePos) {
    UIElement::onClick(relativePos);
    callbackFunc();
}

}
