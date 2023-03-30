//
// Created by thijs on 6-1-23.
//

#include <memory>
#include "Sprite.h"
#include "window/render/Texture2D.h"

namespace PG {

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

const std::unique_ptr<Texture2D> &Sprite::getTexture() const {
    return texture;
}

const std::string &Sprite::getTextureName() const {
    return textureName;
}

}
