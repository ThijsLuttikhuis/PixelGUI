//
// Created by Thijs on 15/04/2023.
//

#ifndef PIXELGUI_SPRITECOMPOSITE_H
#define PIXELGUI_SPRITECOMPOSITE_H

#include <vector>
#include <memory>
#include "glm/vec2.hpp"

#include "ui/uielement/UIElement.h"

namespace PG {

class Sprite;

class SpriteComposite {
private:
    std::vector<std::shared_ptr<Sprite>> sprites;
    std::vector<glm::vec2> positions;
    std::vector<glm::vec2> sizes;

public:
    SpriteComposite() = default;

    virtual ~SpriteComposite() = default;

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
              const std::shared_ptr<Sprite> &referenceSprite, const glm::vec2 &position, const glm::vec2 &size, float baseZIndex);

    /// add sprite
    void addSprite(const std::shared_ptr<Sprite> &sprite, glm::vec2 position, glm::vec2 size);

    /// get sprites
    [[nodiscard]] const std::vector<std::shared_ptr<Sprite>> &getSprites() const;
};

}

#endif //PIXELGUI_SPRITECOMPOSITE_H
