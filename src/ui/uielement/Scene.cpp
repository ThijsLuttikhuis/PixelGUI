//
// Created by Thijs on 31/03/2023.
//

#include <iostream>
#include "Scene.h"

namespace PG {

std::shared_ptr<UIElement> UIElement::getSharedFromThis() {
    return shared_from_this();
}

void Scene::onClick(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - position;

    for (auto &uiElement: children) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onClick(relativeToScene);
        }
    }

    draggingChildPtr = std::weak_ptr<UIElement>();
}

void Scene::onHover(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - position;
    for (auto &uiElement: children) {
        if (uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onHover(relativeToScene);
        }
    }
}

void Scene::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    glm::vec2 relativeToScenePos = mousePos - position;
    glm::vec2 relativeToSceneDragStartPos = dragStartPos - position;

    if (!draggingChildPtr.expired()) {
        auto draggingChild = std::shared_ptr<UIElement>(draggingChildPtr);

        draggingChild->onDrag(relativeToScenePos, relativeToSceneDragStartPos);
        return;
    }

    for (auto &uiElement: children) {
        if (uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScenePos)) {
            uiElement->onDrag(relativeToScenePos, relativeToSceneDragStartPos);
            draggingChildPtr = uiElement;
        }
    }
}

void Scene::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    children.push_back(uiElement);
    uiElement->setParent(getSharedFromThis());
}

void Scene::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                 const std::unique_ptr<TextRenderer> &textRenderer) {

    if (!visible) {
        return;
    }
    if (sprite) {
        SpriteArgs args = SpriteArgs(1.0f);

        sprite->draw(spriteRenderer, position, size, args);
    }

    for (auto &uiElement: children) {
        spriteRenderer->setBaseUI(getSharedFromThis());
        textRenderer->setBaseUI(getSharedFromThis());

        uiElement->draw(spriteRenderer, textRenderer);
    }
}

}