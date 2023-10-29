//
// Created by Thijs on 31/03/2023.
//

#include "Scene.h"
#include "Draggable.h"

namespace PG {


void Scene::onClick(glm::vec2 mousePos) {
    draggingChildPtr = std::weak_ptr<UIElement>();

    if (boundObjectsInBox) {
        glm::vec2 relativeToScene = mousePos - getPosition();
        relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), getSize() - 1.0f);
        mousePos = relativeToScene + getPosition();
    }

    Container::onClick(mousePos);
}

void Scene::onRelease(glm::vec2 mousePos) {
    draggingChildPtr = std::weak_ptr<UIElement>();

    if (boundObjectsInBox) {
        glm::vec2 relativeToScene = mousePos - getPosition();
        relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), getSize() - 1.0f);
        mousePos = relativeToScene + getPosition();
    }

    Container::onRelease(mousePos);
}

void Scene::onHover(glm::vec2 mousePos) {
    if (boundObjectsInBox) {
        glm::vec2 relativeToScene = mousePos - getPosition();
        relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), getSize() - 1.0f);
        mousePos = relativeToScene + getPosition();
    }

    Container::onHover(mousePos);
}

void Scene::onKeyboardKey(int key, int action, int scanCode, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    if (!textInputChildPtr.expired()) {
        auto textInputChild = std::shared_ptr<UIElement>(textInputChildPtr);
        textInputChild->onKeyboardKey(key, action, scanCode,keysPressed);
        return;
    }

    Container::onKeyboardKey(key, action, scanCode, keysPressed);
}

void Scene::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    glm::vec2 relativeToScenePos = mousePos - getPosition();
    glm::vec2 relativeToSceneDragStartPos = dragStartPos - getPosition();

    // check if dragging on a child object, and update if so
    if (draggingChildPtr.expired()) {
        bool newDraggingChild = updateDraggingChild(relativeToScenePos);
        if (!newDraggingChild) {
            return;
        }
    }

    if (boundObjectsInBox) {
        relativeToScenePos = glm::clamp(relativeToScenePos, glm::vec2(0), getSize() - 1.0f);
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

void Scene::setDraggingChild(const std::weak_ptr<UIElement> &uiElement) {
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

void Scene::setTextInputChild(const std::weak_ptr<UIElement> &uiElement) {
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

void Scene::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    children.push_back(uiElement);
    uiElement->setParent(std::dynamic_pointer_cast<Scene>(getSharedFromThis()));
}

void Scene::removeUIElement(int index) {
    if (index < 0 || index >= (int) children.size()) {
        throw messageException("Container::removeUIElement: index " + std::to_string(index) + "does not exist!");
    }
    children.erase(children.begin() + index);
}

void Scene::removeUIElement(const std::shared_ptr<UIElement> &uiElement) {
    int index = getChildIndex(uiElement);
    removeUIElement(index);
}

} // PG