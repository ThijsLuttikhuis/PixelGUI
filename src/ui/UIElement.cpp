//
// Created by thijs on 13-06-22.
//

#include "UIElement.h"
#include "Sprite.h"

namespace PG {

void UIElement::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer) const {
    (void) textRenderer;

    SpriteArgs args = SpriteArgs(1.0f);

    spriteRenderer->drawSprite(sprite, position, size, args);
}

void UIElement::setColor(const glm::vec3 &color_) {
    sprite->setColor(color_);
}

bool UIElement::isPositionInBox(double x, double y, glm::vec2 position, glm::vec2 size) {
    bool xInBox = x > position.x && x < position.x + size.x;
    bool yInBox = y > position.y && y < position.y + size.y;
    return xInBox && yInBox;
}

bool UIElement::isPositionInBox(double x, double y) const {
    return isPositionInBox(x, y, position, size);
}

bool UIElement::isMouseHovering(double xPos, double yPos) const {
    return isPositionInBox(xPos, yPos);
}

void UIElement::setAlpha(float alpha_) {
    sprite->setAlpha(alpha_);
}

const std::unique_ptr<Sprite> &UIElement::getSprite() const {
    return sprite;
}

}