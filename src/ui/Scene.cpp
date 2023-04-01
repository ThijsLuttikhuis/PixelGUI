//
// Created by Thijs on 31/03/2023.
//

#include "Scene.h"

namespace PG {

std::shared_ptr<UIElement> UIElement::getSharedFromThis() {
    return shared_from_this();
}

void Scene::onClick(glm::vec2 relativePos) {
    glm::vec2  relativeToScene = relativePos - position;

    for (auto &uiElement: uiElements) {
        if (!uiElement->isEnabled() || uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onClick(relativeToScene);
        }
    }
}

void Scene::onHover(glm::vec2 relativePos) {
    glm::vec2 relativeToScene = relativePos - position;
    for (auto &uiElement: uiElements) {
        if (uiElement->isHidden()) {
            continue;
        }
        if (uiElement->isMouseHovering(relativeToScene)) {
            uiElement->onHover(relativeToScene);
        }
    }
}

void Scene::addUIElement(const std::shared_ptr<UIElement> &uiElement) {
    uiElements.push_back(uiElement);
}

void Scene::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                 const std::unique_ptr<TextRenderer> &textRenderer) {

    if (!visible) {
        return;
    }
    if (sprite) {
        SpriteArgs args = SpriteArgs(1.0f);

        spriteRenderer->drawSprite(sprite, position, size, args);
    }
    spriteRenderer->setBaseUI(getSharedFromThis());
    textRenderer->setBaseUI(getSharedFromThis());
    for (auto &uiElement : uiElements) {
        uiElement->draw(spriteRenderer, textRenderer);
    }
}

}