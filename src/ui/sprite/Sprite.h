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
public:
    enum NamedZIndex : int {

    };
protected:
    std::string textureName;
    glm::vec3 color;
    float alpha;

    float zIndex = 0.5f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 blendColor = glm::vec3(1.0f);

public:
    explicit Sprite(std::string textureName, glm::vec3 color = glm::vec3(1.0f), float alpha = 1.0f)
          : textureName(std::move(textureName)), color(color), alpha(alpha) { }

    virtual ~Sprite() = default;

    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
                      const glm::vec2 &position, const glm::vec2 &size, float baseZIndex);

    void setColor(const glm::vec3 &color_);

    void setBlendColor(const glm::vec3 &color);

    void setAlpha(float alpha_);

    void setZIndex(float zIndex_);

    [[nodiscard]] std::shared_ptr<Sprite> getSharedFromThis();

    [[nodiscard]] const std::string &getTextureName() const;

    [[nodiscard]] const glm::vec3 &getColor() const;

    [[nodiscard]] const glm::vec3 &getBlendColor() const;

    [[nodiscard]] float getAlpha() const;

    [[nodiscard]] float getZIndex() const;

    [[nodiscard]] const glm::mat4 &getModel() const;


};

}

#endif //PIXELGUI_SPRITE_H
