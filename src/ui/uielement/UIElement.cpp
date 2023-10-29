//
// Created by thijs on 13-06-22.
//

#include <utility>

#include "utilities/DebugPrinter.h"
#include "ui/sprite/Sprite.h"
#include "Scene.h"
#include "RootScene.h"

#include "UIElement.h"

namespace PG {

int UIElement::uniqueIDCounter = 0;

int UIElement::getUniqueID() const {
    return uniqueID;
}

std::shared_ptr<UIElement> UIElement::getSharedFromThis() {
    return shared_from_this();
}

void UIElement::forceSetUniqueID(int uniqueID_) {
    uniqueID = uniqueID_;
}

const std::string &UIElement::getName() const {
    return name;
}

bool UIElement::hasSprite() const {
    return sprite != nullptr;
}

const std::shared_ptr<Sprite> &UIElement::getSprite() const {
    return sprite;
}

bool UIElement::hasParent() const {
    return !parentPtr.expired();
}

std::shared_ptr<Scene> UIElement::getParent() const {
    if (!hasParent()) {
        throw messageException("UIElement::getParent: parent deleted :(");
    }
    return std::shared_ptr<Scene>(parentPtr);
}

std::vector<std::shared_ptr<UIElement>> Scene::getSiblings() {
    if (!hasParent()) {
        auto onlyChildUIElement = getSharedFromThis();
        return {onlyChildUIElement};
    }

    auto parent = getParent();
    return parent->getChildren();
}

void UIElement::setParent(std::weak_ptr<Scene> parent_) {
    parentPtr = std::move(parent_);
}

glm::vec2 UIElement::getPosition() const {
    return position;
}

void UIElement::setPosition(glm::vec2 position_, pgu::positionAnchor anchor) {
    if (hasParent()) {
        position_ = pgu::convertPosition(position_, anchor, getParent());
    }
    position = position_;
}

void UIElement::setPosition(int left, int up, pgu::positionAnchor anchor) {
    setPosition({left, up}, anchor);
}

void UIElement::setPosition(glm::vec2 position_) {
    position = position_;
}

void UIElement::setPosition(int left, int up) {
    setPosition(glm::vec2(left, up));
}

glm::vec2 UIElement::getSize() const {
    return size;
}

void UIElement::setSize(glm::vec2 size_) {
    size = size_;
}

void UIElement::setSize(int width, int height) {
    setSize(glm::vec2(width, height));
}

bool UIElement::isPositionInBox(double x, double y, glm::vec2 position_, glm::vec2 size_, float insideEdge) {
    bool xInBox = x >= position_.x + insideEdge && x <= position_.x + size_.x - insideEdge;
    bool yInBox = y >= position_.y + insideEdge && y <= position_.y + size_.y - insideEdge;
    return xInBox && yInBox;
}

bool UIElement::isPositionInBox(double x, double y, float insideEdge) const {
    return isPositionInBox(x, y, position, size, insideEdge);
}

bool UIElement::isMouseHovering(double xPos, double yPos) const {
    return isPositionInBox(xPos, yPos);
}

bool UIElement::isMouseHovering(const glm::vec2 &pos) const {
    return isPositionInBox(pos.x, pos.y);
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


int UIElement::getKeyboardKey() const {
    return keyboardKey;
}

bool UIElement::isPressed(double xPos, double yPos) const {
    return enabled && isMouseHovering(xPos, yPos);
}

bool UIElement::isKeyPressed(int key) const {
    return enabled && (key == keyboardKey);
}

void
UIElement::onKeyboardKey(int key, int action, int scanCode, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    (void) key, (void) action, (void) scanCode, (void) keysPressed;

    if (keyboardKey == key) {
        DebugPrinter::print(DebugPrinter::DEBUG_KEYBOARD_KEYS, "Pressed key for:     UIElement ", name);
    }
}

std::shared_ptr<Window> UIElement::getWindow() {
    auto rootScene = getRootScene();
    return rootScene->getWindow();
}

glm::vec2 UIElement::getAbsoluteMousePosition() {
    auto rootScene = getRootScene();
    return rootScene->getAbsoluteMousePosition();
}

std::shared_ptr<RootScene> UIElement::getRootScene() {
    if (hasParent()) {
        auto parent = std::shared_ptr<Scene>(parentPtr);
        return parent->getRootScene();
    } else {
        throw messageException("Root UIElement is not of type RootScene");
    }
}

void UIElement::onHover(glm::vec2 mousePos) {
    (void) mousePos;

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_POSITION_UIELEMENT, "Hovering on:  UIElement ", name);
}

void UIElement::onClick(glm::vec2 mousePos) {
    (void) mousePos;

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Pressed on:     UIElement ", name);
}

void UIElement::onRelease(glm::vec2 mousePos) {
    (void) mousePos;

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Released on:    UIElement ", name);

}

void UIElement::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    (void) mousePos, (void) dragStartPos;

    DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Dragging on:    UIElement ", name);
}

void UIElement::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {

    if (!visible || !sprite) {
        return;
    }
    sprite->draw(spriteRenderer, textRenderer, position, size, baseZIndex);
}

} // PG
