//
// Created by Thijs on 31/03/2023.
//

#include <algorithm>
#include "Scene.h"
#include "Draggable.h"

namespace PG {

std::shared_ptr<UIElement> UIElement::getSharedFromThis() {
    return shared_from_this();
}

void Scene::onClick(glm::vec2 mousePos) {
    glm::vec2 relativeToScene = mousePos - position;

    if (boundObjectsInBox) {
        relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), size - 1.0f);
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
        relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), size - 1.0f);
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
        relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), size - 1.0f);
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

void Scene::onKeyboardKey(int key, int action, int scanCode, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    if (!textInputChildPtr.expired()) {
        auto textInputChild = std::shared_ptr<UIElement>(textInputChildPtr);
        textInputChild->onKeyboardKey(key, action, scanCode,keysPressed);
        return;
    }

    for (auto &uiElement: children) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }

        uiElement->onKeyboardKey(key, action, scanCode, keysPressed);
    }
}

void Scene::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    glm::vec2 relativeToScenePos = mousePos - position;
    glm::vec2 relativeToSceneDragStartPos = dragStartPos - position;

    // check if dragging on a child object, and update if so
    if (draggingChildPtr.expired()) {
        bool newDraggingChild = updateDraggingChild(relativeToScenePos);
        if (!newDraggingChild) {
            return;
        }
    }

    if (boundObjectsInBox) {
        relativeToScenePos = glm::clamp(relativeToScenePos, glm::vec2(0), size - 1.0f);
    }

    auto draggingChild = std::shared_ptr<UIElement>(draggingChildPtr);
    draggingChild->onDrag(relativeToScenePos, relativeToSceneDragStartPos);

    // update ownership of dragging child if the mouse is not on this scene
    if (changeOwnerMode == alwaysAllowOwnerChange || changeOwnerMode == onlyGiveUIElements) {
        if (!isMouseHovering(mousePos)) {
            auto draggingChildDraggable = std::dynamic_pointer_cast<Draggable>(draggingChild);
            if (draggingChildDraggable) {
                updateOwnerChange(draggingChild, mousePos, dragStartPos);
            }
        }
    }
}

bool Scene::updateDraggingChild(glm::vec2 &relativeToScenePos) {
    return std::any_of(children.cbegin(), children.cend(),
                       [relativeToScenePos, this](auto uiElement) {

                           if (uiElement->isHidden() || !uiElement->isMouseHovering(relativeToScenePos)) {
                               return false;
                           }
                           this->draggingChildPtr = uiElement;
                           return true;
                       });
}

bool Scene::updateOwnerChange(const std::shared_ptr<UIElement> &draggingChild,
                              const glm::vec2 &mousePos, const glm::vec2 &dragStartPos) {

    auto siblings = getSiblings();
    for (auto &sibling: siblings) {
        auto siblingScene = std::dynamic_pointer_cast<Scene>(sibling);
        if (!siblingScene) {
            continue;
        }
        if (siblingScene->getChangeOwnerMode() != alwaysAllowOwnerChange &&
            siblingScene->getChangeOwnerMode() != onlyReceiveUIElements) {
            continue;
        }
        if (siblingScene == getSharedFromThis()) {
            continue;
        }

        // check if dragging child is on a different scene, if so, change ownership to that scene
        glm::vec2 siblingPos = siblingScene->getPosition();
        glm::vec2 siblingSize = siblingScene->getSize();
        if (isPositionInBox(mousePos.x, mousePos.y,
                            siblingPos, siblingSize)) {

            bool ownerChanged = changeOwner(draggingChild, siblingScene);
            if (!ownerChanged) {
                throw std::exception();
            }

            glm::vec2 relativeToScenePos = mousePos - siblingPos;
            glm::vec2 relativeToSceneDragStartPos = dragStartPos - siblingPos;
            draggingChild->onDrag(relativeToScenePos, relativeToSceneDragStartPos);

            return ownerChanged;
        }
    }
    return false;
}

bool Scene::changeOwner(const std::shared_ptr<UIElement> &uiElementToChange, const std::shared_ptr<Scene> &newOwner) {

    int index = getChildIndex(uiElementToChange);
    if (index < 0 || index >= (int) children.size()) {
        return false;
    }
    if (changeOwnerMode != alwaysAllowOwnerChange && changeOwnerMode != onlyGiveUIElements) {
        return false;
    }
    if (newOwner->changeOwnerMode != alwaysAllowOwnerChange && newOwner->changeOwnerMode != onlyReceiveUIElements) {
        return false;
    }

    DebugPrinter::print(DebugPrinter::ALL, "Changing owner of ", uiElementToChange->getName(), " from ", getName(),
                        " to ", newOwner->getName());

    children.erase(children.begin() + index);
    newOwner->addUIElement(uiElementToChange);

    if (!draggingChildPtr.expired()) {
        auto draggingChild = std::shared_ptr<UIElement>(draggingChildPtr);
        if (draggingChild == uiElementToChange) {
            newOwner->setDraggingChild(draggingChild);
            draggingChildPtr = std::weak_ptr<UIElement>();
        }
    }
    return true;
}

void Scene::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    children.push_back(uiElement);
    uiElement->setParent(std::dynamic_pointer_cast<Scene>(getSharedFromThis()));
}

void Scene::removeUIElement(int index) {
    if (index < 0 || index >= (int) children.size()) {
        throw messageException("Scene::removeUIElement: index " + std::to_string(index) + "does not exist!");
    }
    children.erase(children.begin() + index);
}

void Scene::removeUIElement(const std::shared_ptr<UIElement> &uiElement) {
    int index = getChildIndex(uiElement);
    removeUIElement(index);
}

void Scene::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                 const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {

    if (!visible) {
        return;
    }
    if (sprite) {
        sprite->draw(spriteRenderer, textRenderer, position, size, baseZIndex);
    }

    for (auto &uiElement: children) {
        spriteRenderer->setBaseUI(getSharedFromThis());
        textRenderer->setBaseUI(getSharedFromThis());

        uiElement->draw(spriteRenderer, textRenderer, 1.0f - (baseZIndex / 2.0f));
    }
}

void Scene::setDraggingChild(const std::shared_ptr<UIElement> &uiElement) {
    draggingChildPtr = uiElement;

    if (hasParent()) {
        getParent()->setDraggingChild(getSharedFromThis());
    }
}

void Scene::clearDraggingChild() {
    draggingChildPtr = std::weak_ptr<UIElement>();

    if (hasParent()) {
        getParent()->clearDraggingChild();
    }
}

void Scene::setTextInputChild(const std::shared_ptr<UIElement> &uiElement) {
    textInputChildPtr = uiElement;

    if (hasParent()) {
        getParent()->setTextInputChild(getSharedFromThis());
    }
}

void Scene::clearTextInputChild() {
    textInputChildPtr = draggingChildPtr = std::weak_ptr<UIElement>();

    if (hasParent()) {
        getParent()->clearTextInputChild();
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
    if (!hasParent()) {
        auto onlyChildUIElement = getSharedFromThis();
        return {onlyChildUIElement};
    }

    auto parent = getParent();
    return parent->getChildren();
}

std::vector<std::shared_ptr<UIElement>> Scene::getChildren() {
    return children;
}

int Scene::getChildIndex(const std::shared_ptr<UIElement> &uiElement) {
    for (int i = 0; i < (int) children.size(); i++) {
        if (uiElement == children[i]) {
            return i;
        }
    }

    DebugPrinter::print(DebugPrinter::ALL, "Scene::getChildIndex: ", uiElement->getName(), " not found");
    return -1;
}

std::shared_ptr<UIElement> Scene::getDraggingChild() {
    if (draggingChildPtr.expired()) {
        return {};
    }
    return std::shared_ptr<UIElement>(draggingChildPtr);
}

std::shared_ptr<UIElement> Scene::getTextInputChild() {
    if (textInputChildPtr.expired()) {
        return {};
    }
    return std::shared_ptr<UIElement>(textInputChildPtr);
}

}
