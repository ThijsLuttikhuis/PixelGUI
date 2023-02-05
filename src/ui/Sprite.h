//
// Created by thijs on 6-1-23.
//

#ifndef PIXELGUI_SPRITE_H
#define PIXELGUI_SPRITE_H

#include <utility>
#include <glm/vec3.hpp>
#include "window/render/Texture2D.h"

namespace PG {

class Sprite {
private:
    std::string textureName;
    std::unique_ptr<Texture2D> texture;
    glm::vec3 color;
    float alpha;

public:
    Sprite(std::string textureName, glm::vec3 color, float alpha)
          : textureName(std::move(textureName)), color(color), alpha(alpha) {
    };

    void setColor(const glm::vec3 &color_);

    void setAlpha(float alpha_);

    [[nodiscard]] const std::unique_ptr<Texture2D> &getTexture() const;

    [[nodiscard]] const glm::vec3 &getColor() const;

    [[nodiscard]] float getAlpha() const;
};

}

#endif //PIXELGUI_SPRITE_H
