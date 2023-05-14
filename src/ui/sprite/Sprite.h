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
public:
    enum sceneAnchor {
        BOTTOM_LEFT_SCENE = 1,
        BOTTOM_SCENE = 2,
        BOTTOM_RIGHT_SCENE = 3,
        LEFT_SCENE = 4,
        MIDDLE_SCENE = 5,
        RIGHT_SCENE = 6,
        TOP_LEFT_SCENE = 7,
        TOP_SCENE = 8,
        TOP_RIGHT_SCENE = 9,
    };
    enum selfAnchor {
        BOTTOM_LEFT_SELF = 1,
        BOTTOM_SELF = 2,
        BOTTOM_RIGHT_SELF = 3,
        LEFT_SELF = 4,
        MIDDLE_SELF = 5,
        RIGHT_SELF = 6,
        TOP_LEFT_SELF = 7,
        TOP_SELF = 8,
        TOP_RIGHT_SELF = 9,
    };
    enum NamedZIndex : int {

    };
protected:
    std::string textureName;
    glm::vec3 color;
    float alpha;

    float zIndex = 0.5f;
    sceneAnchor sceneAnchor_ = TOP_LEFT_SCENE;
    selfAnchor selfAnchor_ = TOP_LEFT_SELF;
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
