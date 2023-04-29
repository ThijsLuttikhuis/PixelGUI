//
// Created by Thijs on 31/03/2023.
//

#include "Scene.h"

namespace PG {

std::shared_ptr<UIElement> UIElement::getSharedFromThis() {
    return shared_from_this();
}

void Scene::onClick(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - position;

    draggingChildPtr = std::weak_ptr<UIElement>();

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

void Scene::onRelease(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - position;

    draggingChildPtr = std::weak_ptr<UIElement>();

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

        if (boundObjectsInBox) {
            relativeToScenePos.x = relativeToScenePos.x < 0 ? 0 : relativeToScenePos.x;
            relativeToScenePos.x = relativeToScenePos.x > size.x ? size.x : relativeToScenePos.x;
            relativeToScenePos.y = relativeToScenePos.y < 0 ? 0 : relativeToScenePos.y;
            relativeToScenePos.y = relativeToScenePos.y > size.y ? size.y : relativeToScenePos.y;
        }

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
    uiElement->setParent(std::dynamic_pointer_cast<Scene>(getSharedFromThis()));
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

void Scene::setDraggingChildPtr(const std::shared_ptr<UIElement> &uiElement) {
    draggingChildPtr = uiElement;

    if (hasParent()) {
        auto parent = std::shared_ptr<Scene>(parentPtr);
        parent->setDraggingChildPtr(getSharedFromThis());
    }
}

void Scene::setBoundObjectsInBox(bool boundObjects) {
    boundObjectsInBox = boundObjects;
}

bool Scene::getChangeOwnerWhenDraggingOutsideScene() const {
    return changeOwnerWhenDraggingOutsideScene;
}

void Scene::setChangeOwnerWhenDraggingOutsideScene(bool changeOwner) {
    changeOwnerWhenDraggingOutsideScene = changeOwner;
}

std::vector<std::shared_ptr<UIElement>> Scene::getSiblings() {
    if (parentPtr.expired()) {
        auto onlyChildUIElement = getSharedFromThis();
        return {onlyChildUIElement};
    }

    auto parent = std::shared_ptr<Scene>(parentPtr);
    return parent->getChildren();
}

std::vector<std::shared_ptr<UIElement>> Scene::getChildren() {
    return children;
}

bool Scene::changeOwner(const std::shared_ptr<UIElement> &uiElementToChange, const std::shared_ptr<Scene> &newOwner) {
    for (unsigned long i = 0; i < children.size(); i++) {
        if (uiElementToChange == children[i]) {
            children.erase(children.begin() + i);
            newOwner->addUIElement(uiElementToChange);
            uiElementToChange->setPosition(uiElementToChange->getPosition() + position - newOwner->getPosition());

            if (!draggingChildPtr.expired()) {
                auto draggingChild = std::shared_ptr<UIElement>(draggingChildPtr);
                if (draggingChild == uiElementToChange) {
                    newOwner->setDraggingChildPtr(draggingChild);
                    draggingChildPtr = std::weak_ptr<UIElement>();
                }
            }
            return true;

        }
    }
    return false;
}

}
