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

    if (boundObjectsInBox) {
        relativeToScene = pgu::clampVec(relativeToScene, glm::vec2(0), size - 1.0f);
    }

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

    if (boundObjectsInBox) {
        relativeToScene = pgu::clampVec(relativeToScene, glm::vec2(0), size - 1.0f);
    }

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

    if (boundObjectsInBox) {
        relativeToScene = pgu::clampVec(relativeToScene, glm::vec2(0), size - 1.0f);
    }

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

    auto draggingChild = std::shared_ptr<UIElement>(draggingChildPtr);
    draggingChild->onDrag(relativeToScenePos, relativeToSceneDragStartPos);

    glm::vec2 draggingChildPos = draggingChild->getPosition();
    if (!boundObjectsInBox && isPositionInBox(draggingChildPos.x, draggingChildPos.y, glm::vec2(0.0f), size - 1.0f)) {
        return;
    }
    if (changeOwnerMode != alwaysAllowOwnerChange && changeOwnerMode != onlyGiveUIElements) {
        return;
    }

    updateOwnerChange(draggingChild, draggingChildPos);

    if (boundObjectsInBox) {
        relativeToScenePos = pgu::clampVec(relativeToScenePos, glm::vec2(0), size - 1.0f);
        draggingChild->onDrag(relativeToScenePos, relativeToSceneDragStartPos);
    }

}

bool Scene::updateOwnerChange(const std::shared_ptr<UIElement> &draggingChild, const glm::vec2 &draggingChildPos) {
    auto siblings = getSiblings();
    for (auto &sibling: siblings) {
        auto siblingScene = std::dynamic_pointer_cast<Scene>(sibling);
        if (!siblingScene) {
            continue;
        }
        if (siblingScene->getChangeOwnerMode() != alwaysAllowOwnerChange && siblingScene->getChangeOwnerMode() != onlyReceiveUIElements) {
            continue;
        }
        if (siblingScene == getSharedFromThis()) {
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
            return ownerChanged;
        }
    }
    return false;
}

bool Scene::updateDraggingChild(glm::vec2 &relativeToScenePos, glm::vec2 &relativeToSceneDragStartPos) {
    for (auto &uiElement: children) {
        if (uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScenePos)) {
            uiElement->onDrag(relativeToScenePos, relativeToSceneDragStartPos);
            draggingChildPtr = uiElement;
            return true;
        }
    }
    return false;
}

void Scene::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    children.push_back(uiElement);
    uiElement->setParent(std::dynamic_pointer_cast<Scene>(getSharedFromThis()));
}

void Scene::removeUIElement(int index) {
    if (index < 0 || index >= (int)children.size()) {
        throw std::exception();
    }
    children.erase(children.begin() + index);
}

void Scene::removeUIElement(const std::shared_ptr<UIElement> &uiElement) {
    int index = getChildIndex(uiElement);
    removeUIElement(index);
}

void Scene::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                 const std::unique_ptr<TextRenderer> &textRenderer) {

    if (!visible) {
        return;
    }
    if (sprite) {
        auto args = std::make_shared<SpriteArgs>(1.0f);
        sprite->draw(spriteRenderer, textRenderer, position, size, args);
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

enum Scene::changeOwnerMode Scene::getChangeOwnerMode() const {
    return changeOwnerMode;
}

void Scene::setChangeOwnerMode(enum changeOwnerMode changeOwner_) {
    changeOwnerMode = changeOwner_;
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
    if (changeOwnerMode != alwaysAllowOwnerChange && changeOwnerMode != onlyGiveUIElements) {
        return false;
    }
    if (newOwner->changeOwnerMode != alwaysAllowOwnerChange && newOwner->changeOwnerMode != onlyReceiveUIElements) {
        return false;
    }

    DebugPrinter::print(DebugPrinter::ALL, "Changing owner of " , uiElementToChange->getName(), " from ", getName(), " to ", newOwner->getName());
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

    DebugPrinter::print(DebugPrinter::ALL, "Scene::getChildIndex: ", uiElement->getName(), " not found");
    return -1;
}

}
