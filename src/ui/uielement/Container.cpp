//
// Created by Thijs on 31/03/2023.
//

#include <algorithm>
#include "Container.h"
#include "Scene.h"

namespace PG {

void Container::onClick(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - getPosition();

    for (auto &uiElement: children) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onClick(relativeToScene);
            return;
        }
    }
}

void Container::onRelease(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - getPosition();

    for (auto &uiElement: children) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onRelease(relativeToScene);
            return;
        }
    }
}

void Container::onHover(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - getPosition();

    for (auto &uiElement: children) {
        if (uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onHover(relativeToScene);
        }
    }
}

void Container::onKeyboardKey(int key, int action, int scanCode, const std::unique_ptr<std::vector<bool>> &keysPressed) {

    for (auto &uiElement: children) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        uiElement->onKeyboardKey(key, action, scanCode, keysPressed);
    }
}

void Container::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    glm::vec2 relativeToScene = mousePos - getPosition();

    for (auto &uiElement: children) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onDrag(relativeToScene, dragStartPos);
            return;
        }
    }
}


void Container::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {

    if (!isVisible()) {
        return;
    }
    if (hasSprite()) {
        getSprite()->draw(spriteRenderer, textRenderer, getPosition(), getSize(), baseZIndex);
    }

    for (auto &uiElement: children) {
        spriteRenderer->setBaseUI(std::dynamic_pointer_cast<Container>(getSharedFromThis()));
        textRenderer->setBaseUI(std::dynamic_pointer_cast<Container>(getSharedFromThis()));

        uiElement->draw(spriteRenderer, textRenderer, 0.5f + 0.5f * baseZIndex);
    }
}

std::vector<std::shared_ptr<UIElement>> Container::getChildren() {
    return children;
}

int Container::getChildIndex(const std::shared_ptr<UIElement> &uiElement) {
    for (int i = 0; i < (int) children.size(); i++) {
        if (uiElement == children[i]) {
            return i;
        }
    }

    DebugPrinter::print(DebugPrinter::ALL, "Container::getChildIndex: ", uiElement->getName(), " not found");
    return -1;
}

void Container::setPosition(glm::vec2 position_) {
    UIElement::setPosition(position_);
}

void Container::setPosition(int left, int up) {
    UIElement::setPosition(left, up);
}

void Container::setPosition(glm::vec2 position_, pgu::positionAnchor anchor) {
    UIElement::setPosition(position_, anchor);

    if (hasParent()) {
        globalPosition = position_ + getParent()->getGlobalPosition();
    }
    else {
        globalPosition = position_;
    }
}

void Container::setPosition(int left, int up, pgu::positionAnchor anchor) {
    UIElement::setPosition(left, up, anchor);
}

glm::vec2 Container::getGlobalPosition() const {
    return globalPosition;
}

void Container::setGlobalPosition(glm::vec2 globalPosition_) {
    globalPosition = globalPosition_;

    if (hasParent()) {
        setPosition(globalPosition_ - getParent()->getGlobalPosition());
    }
    else {
        setPosition(globalPosition_);
    }
}

void Container::setGlobalPosition(int left, int up) {
    setGlobalPosition(glm::vec2(left, up));
}

void Container::setParent(std::weak_ptr<Scene> parent_) {
    UIElement::setParent(parent_);

    globalPosition = getPosition() + getParent()->getGlobalPosition();
}

}
