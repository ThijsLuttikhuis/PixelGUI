//
// Created by thijs on 6-1-23.
//

#ifndef PIXELGUI_SPRITE_H
#define PIXELGUI_SPRITE_H

#include <utility>
#include "glm-0.9.7.1/glm/vec3.hpp"
#include "window/render/Texture2D.h"
#include "window/render/SpriteRenderer.h"
#include "window/render/TextRenderer.h"

namespace PG {

class Sprite : virtual public std::enable_shared_from_this<Sprite> {
private:
    std::string textureName;
    glm::vec3 color;
    float alpha;

public:
    explicit Sprite(std::string textureName)
          : textureName(std::move(textureName)), color(glm::vec3(1.0f)), alpha(1.0f) {
    }

    Sprite(std::string textureName, glm::vec3 color, float alpha)
          : textureName(std::move(textureName)), color(color), alpha(alpha) {
    }

    virtual ~Sprite() = default;

    /// render
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const glm::vec2 &position, const glm::vec2 &size, const SpriteArgs &args);

    /// setters
    void setColor(const glm::vec3 &color_);

    void setAlpha(float alpha_);

    /// getters
    [[nodiscard]] std::shared_ptr<Sprite> getSharedFromThis();

    [[nodiscard]] const std::string &getTextureName() const;

    [[nodiscard]] const glm::vec3 &getColor() const;

    [[nodiscard]] float getAlpha() const;
};

}

#endif //PIXELGUI_SPRITE_H
