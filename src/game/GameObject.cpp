//
// Created by thijs on 30-05-22.
//

#include "GameObject.h"

namespace PG {

int GameObject::uniqueIDCounter = 0;

int GameObject::getUniqueID() const {
    return uniqueID;
}

const glm::vec2 &GameObject::getPosition() const {
    return position;
}

const glm::vec2 &GameObject::getSize() const {
    return size;
}

const std::string &GameObject::getName() const {
    return name;
}

bool GameObject::isMouseHovering(double xPos, double yPos) const {
    return isPositionInBox(xPos, yPos, position, size);
}

bool GameObject::isMouseHovering() const {
    return mouseIsHovering;
}

void GameObject::setIsMouseHovering(bool hover_) {
    mouseIsHovering = hover_;
}

void GameObject::forceSetUniqueID(int uniqueID_) {
    uniqueID = uniqueID_;
}

void GameObject::setPosition(glm::vec2 position_) {
    position = position_;
}

void GameObject::setSize(glm::vec2 size_) {
    size = size_;
}

void GameObject::setPosition(int left, int up) {
    setPosition(glm::vec2(left, up));
}

void GameObject::setSize(int width, int height) {
    setSize(glm::vec2(width, height));
}

void GameObject::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) const {
    (void) textRenderer;
    SpriteArgs spriteArgs(1.0f);

    spriteRenderer->drawSprite(name, position, size, spriteArgs);
}

bool GameObject::isPositionInBox(double x, double y, glm::vec2 position, glm::vec2 size) {
    bool xInBox = x > position.x && x < position.x + size.x;
    bool yInBox = y > position.y && y < position.y + size.y;
    return xInBox && yInBox;
}

bool GameObject::isPositionInBox(double x, double y) {
    return GameObject::isPositionInBox(x, y, position, size);
}


}
