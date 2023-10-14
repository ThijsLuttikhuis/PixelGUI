//
// Created by Thijs on 02/07/2023.
//

#include "ui/uielement/RootScene.h"
#include "CustomMouseSprite.h"

#include <utility>

namespace PG {

void CustomMouseSprite::setMouse(float rotation_) {
    rotation = rotation_;
    rootScene->setCurrentMouseSprite(std::dynamic_pointer_cast<CustomMouseSprite>(getSharedFromThis()));
}

void CustomMouseSprite::setRootScene(std::shared_ptr<RootScene> rootScene_) {
    rootScene = std::move(rootScene_);
}

void CustomMouseSprite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                             const std::unique_ptr<TextRenderer> &textRenderer, const glm::vec2 &position,
                             const glm::vec2 &size, float baseZIndex) {

    auto offsetPos = position + size * positionOffsetFactor;

    Sprite::draw(spriteRenderer, textRenderer, offsetPos, size, baseZIndex);
}

void CustomMouseSprite::setPositionOffsetFactor(glm::vec2 offsetFactor) {
    positionOffsetFactor = offsetFactor;
}

} // PG
