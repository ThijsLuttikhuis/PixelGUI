//
// Created by Thijs on 13/10/2023.
//

#include "ExtendedScene.h"

namespace PG {


void ExtendedScene::onClick(glm::vec2 mousePos) {
    glm::vec2 relativeToViewPos = mousePos - currentViewPos;
    glm::vec2 relativeToScene = relativeToViewPos - getPosition();

    auto draggingChild = std::weak_ptr<UIElement>();
    setDraggingChild(draggingChild);

    for (auto &uiElement: getChildren()) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onClick(relativeToScene);
            return;
        }
    }

    sceneDragging = true;
}

void ExtendedScene::onRelease(glm::vec2 mousePos) {
    sceneDragging = false;

    glm::vec2 relativeToViewPos = mousePos - currentViewPos;
    glm::vec2 relativeToScene = relativeToViewPos - getPosition();

    relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), getSize() - 1.0f);

    auto draggingChild = std::weak_ptr<UIElement>();
    setDraggingChild(draggingChild);

    for (auto &uiElement: getChildren()) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onRelease(relativeToScene);
            return;
        }
    }

}

void ExtendedScene::onHover(glm::vec2 mousePos) {

    glm::vec2 relativeToViewPos = mousePos - currentViewPos;
    glm::vec2 relativeToScene = relativeToViewPos - getPosition();

    relativeToScene = glm::clamp(relativeToScene, glm::vec2(0), getSize() - 1.0f);

    for (auto &uiElement: getChildren()) {
        if (uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onHover(relativeToScene);
        }
    }
}

void ExtendedScene::onKeyboardKey(int key, int action, int scanCode, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    Scene::onKeyboardKey(key, action, scanCode, keysPressed);
}

void ExtendedScene::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    std::cout << currentViewPos.x << "  " << currentViewPos.y << std::endl;

    if (sceneDragging) {
        currentViewPos = currentViewPos + mousePos - dragStartPos;
    } else {
        Scene::onDrag(mousePos, dragStartPos);
    }
}

void ExtendedScene::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                 const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {

    if (!isVisible()) {
        return;
    }

    setPosition(getPosition() + currentViewPos);

    if (hasSprite()) {
        getSprite()->draw(spriteRenderer, textRenderer, getPosition(), getSize(), baseZIndex);
    }


    for (auto &uiElement: getChildren()) {
        spriteRenderer->setBaseUI(std::dynamic_pointer_cast<Scene>(getSharedFromThis()));
        textRenderer->setBaseUI(std::dynamic_pointer_cast<Scene>(getSharedFromThis()));

        uiElement->draw(spriteRenderer, textRenderer, 0.5f + 0.5f * baseZIndex);
    }

    setPosition(getPosition() - currentViewPos);
}


} // PG
