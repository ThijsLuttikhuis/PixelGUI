//
// Created by thijs on 13-06-22.
//

#include "UIElement.h"
#include "Sprite.h"
#include "utilities/DebugPrinter.h"

namespace PG {

int UIElement::uniqueIDCounter = 0;

int UIElement::getUniqueID() const {
    return uniqueID;
}

const glm::vec2 &UIElement::getPosition() const {
    return position;
}

const glm::vec2 &UIElement::getSize() const {
    return size;
}

const std::string &UIElement::getName() const {
    return name;
}

void UIElement::forceSetUniqueID(int uniqueID_) {
    uniqueID = uniqueID_;
}

void UIElement::setPosition(glm::vec2 position_) {
    position = position_;
}

void UIElement::setSize(glm::vec2 size_) {
    size = size_;
}

void UIElement::setPosition(int left, int up) {
    setPosition(glm::vec2(left, up));
}

void UIElement::setSize(int width, int height) {
    setSize(glm::vec2(width, height));
}

void UIElement::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer) {
    (void) textRenderer;

    if (!visible || !sprite) {
        return;
    }

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

bool UIElement::isMouseHovering(const glm::vec2 &pos) const {
    return isMouseHovering(pos.x, pos.y);
}

void UIElement::setAlpha(float alpha_) {
    sprite->setAlpha(alpha_);
}

const std::unique_ptr<Sprite> &UIElement::getSprite() const {
    return sprite;
}

void UIElement::onHover(glm::vec2 relativePos) {
    (void) relativePos;

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_POSITION_UIELEMENT, "hovering on:  UIElement ", name);
}

void UIElement::onClick(glm::vec2 relativePos) {
    (void) relativePos;

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Pressed on:     UIElement ", name);\
}

bool UIElement::isPressed(double xPos, double yPos) const {
    return enabled && isMouseHovering(xPos, yPos);
}

bool UIElement::isKeyPressed(int key) const {
    return enabled && (key == keyboardKey);
}

bool UIElement::isEnabled() const {
    return enabled;
}

bool UIElement::isVisible() const {
    return visible;
}

bool UIElement::isHidden() const {
    return !visible;
}

void UIElement::setEnabled(bool enabled_) {
    enabled = enabled_;
}

void UIElement::enable() {
    enabled = true;
}

void UIElement::disable() {
    enabled = false;
}

void UIElement::setVisibility(bool visible_) {
    visible = visible_;
}

void UIElement::hide() {
    visible = false;
}

void UIElement::show() {
    visible = true;
}

}
