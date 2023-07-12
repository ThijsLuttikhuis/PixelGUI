//
// Created by Thijs on 14/05/2023.
//

#include "RootScene.h"

#include <utility>

namespace PG {

void RootScene::setWindow(std::weak_ptr<Window> window_) {
    window = std::move(window_);
}

void RootScene::setParent(std::weak_ptr<Scene> scene_) {
    (void) scene_;
    throw messageException("cannot set parent of baseUI since it is the root UIElement");
}

std::shared_ptr<Window> RootScene::getWindow() {
    return std::shared_ptr<Window>(window);
}

std::shared_ptr<RootScene> RootScene::getRootScene() {
    return std::dynamic_pointer_cast<RootScene>(getSharedFromThis());
}

glm::vec2 RootScene::getAbsoluteMousePosition() {
    return mousePosition;
}

void RootScene::onRelease(glm::vec2 mousePos) {
    mousePosition = mousePos;
    if (mouseDownSprite) {
        std::swap(mouseSprite, mouseDownSprite);
    }

    Scene::onRelease(mousePos);
}

void RootScene::onClick(glm::vec2 mousePos) {
    mousePosition = mousePos;
    if (mouseDownSprite) {
        std::swap(mouseSprite, mouseDownSprite);
    }

    Scene::onClick(mousePos);
}

void RootScene::onHover(glm::vec2 mousePos) {
    mousePosition = mousePos;

    Scene::onHover(mousePos);
}

void RootScene::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    mousePosition = mousePos;

    Scene::onDrag(mousePos, dragStartPos);
}

void RootScene::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {

    if (!currentMouseSpritePtr.expired() && isMouseHovering(mousePosition)) {
        auto currentMouseSprite = std::shared_ptr<CustomMouseSprite>(currentMouseSpritePtr);
        currentMouseSprite->draw(spriteRenderer, textRenderer, mousePosition, mouseSize, baseZIndex);
    }
    currentMouseSpritePtr = mouseSprite;

    Scene::draw(spriteRenderer, textRenderer, baseZIndex);
}

void RootScene::forceSetMousePosition(glm::vec2 pos) {
    mousePosition = pos;
}

void RootScene::setCurrentMouseSprite(const std::shared_ptr<CustomMouseSprite> &sprite) {
    currentMouseSpritePtr = sprite;
}

}