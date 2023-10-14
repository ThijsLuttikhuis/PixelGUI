//
// Created by thijs on 6-1-23.
//

#include <memory>
#include <iostream>
#include "Sprite.h"
#include "window/render/Texture2D.h"

namespace PG {

std::shared_ptr<Sprite> Sprite::getSharedFromThis() {
    return shared_from_this();
}

void Sprite::setColor(const glm::vec3 &color_) {
    color = color_;
}

void Sprite::setAlpha(float alpha_) {
    alpha = alpha_;
}

const glm::vec3 &Sprite::getColor() const {
    return color;
}

float Sprite::getAlpha() const {
    return alpha;
}

const std::string &Sprite::getTextureName() const {
    return textureName;
}

void Sprite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                 const std::unique_ptr<TextRenderer> &textRenderer,
             const glm::vec2 &position, const glm::vec2 &size, float baseZIndex) {

    (void) textRenderer;
    spriteRenderer->drawSprite(getSharedFromThis(), position, size, baseZIndex, rotation);
}

float Sprite::getZIndex() const {
    return zIndex;
}

const glm::mat4 &Sprite::getModel() const {
    return model;
}

void Sprite::setBlendColor(const glm::vec3 &color_) {
    blendColor = color_;
}

const glm::vec3 &Sprite::getBlendColor() const {
    return blendColor;
}

void Sprite::setZIndex(float zIndex_) {
    zIndex = zIndex_;
}



} // PG
