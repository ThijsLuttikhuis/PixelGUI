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

    if (draggingChildPtr.expired()) {
        updateDraggingChild(relativeToScenePos, relativeToSceneDragStartPos);
        if (draggingChildPtr.expired()) {
            return;
        }
    }

    if (boundObjectsInBox) {
        relativeToScenePos = pgu::clampVec(relativeToScenePos, glm::vec2(0), size);
    }

    auto draggingChild = std::shared_ptr<UIElement>(draggingChildPtr);
    draggingChild->onDrag(relativeToScenePos, relativeToSceneDragStartPos);

    if (changeOwnerWhenDraggingOutsideScene) {
        glm::vec2 draggingChildPos = draggingChild->getPosition();
        if (isPositionInBox(draggingChildPos.x, draggingChildPos.y, glm::vec2(0.0f), size)) {
            return;
        }

        updateOwnerChange(draggingChild, draggingChildPos);
    }
}

void Scene::updateOwnerChange(const std::shared_ptr<UIElement> &draggingChild, const glm::vec2 &draggingChildPos) {
    auto siblings = getSiblings();
    for (auto &sibling: siblings) {
        auto siblingScene = std::dynamic_pointer_cast<Scene>(sibling);
        if (!siblingScene) {
            continue;
        }
        glm::vec2 relativeSiblingPos = siblingScene->getPosition() - position;
        glm::vec2 siblingSize = siblingScene->getSize();
        if (isPositionInBox(draggingChildPos.x, draggingChildPos.y,
                            relativeSiblingPos, siblingSize)) {

            bool ownerChanged = changeOwner(draggingChild, siblingScene);
            if (!ownerChanged) {
                throw std::exception();
            }
            return;
        }
    }
}

void Scene::updateDraggingChild(glm::vec2 &relativeToScenePos, glm::vec2 &relativeToSceneDragStartPos) {
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

    int index = getChildIndex(uiElementToChange);
    if (index < 0) {
        return false;
    }

    DebugPrinter::print(DebugPrinter::ALL, "Changing owner from ", getName(), " to ", newOwner->getName());
    children.erase(children.begin() + index);
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

int Scene::getChildIndex(const std::shared_ptr<UIElement> &uiElement) {
    for (int i = 0; i < (int)children.size(); i++) {
        if (uiElement == children[i]) {
            return i;
        }
    }

    return -1; //TODO: what to return? -1? children.size()? throw error?
}

}
