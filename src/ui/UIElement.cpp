//
// Created by thijs on 13-06-22.
//

#include "UIElement.h"

namespace PG {

void UIElement::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer) const {
    (void) textRenderer;

    SpriteArgs args = SpriteArgs(1.0f, color, alpha);

    spriteRenderer->drawSprite("box", position, size, args);
}

void UIElement::setColor(const glm::vec3 &color_) {
    color = color_;
}

bool UIElement::isPositionInBox(double x, double y, glm::vec2 position, glm::vec2 size) {
    bool xInBox = x > position.x && x < position.x + size.x;
    bool yInBox = y > position.y && y < position.y + size.y;
    return xInBox && yInBox;
}

bool UIElement::isPositionInBox(double x, double y) {
    return isPositionInBox(x, y, position, size);
}

bool UIElement::isMouseHovering(double xPos, double yPos) const {
    return isPositionInBox(xPos, yPos, position, size);
}

bool UIElement::isMouseHovering() const {
    return mouseIsHovering;
}

void UIElement::setIsMouseHovering(bool hover_) {
    mouseIsHovering = hover_;
}


}