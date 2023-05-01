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
    explicit SpriteComposite(const std::string &prefabString = "rectangle: size: {4,4} edgeColor: {0.3, 0.3, 0.3} fillColor: {1.0, 1.0, 1.0}");

    void prefabRectangle(const std::string &prefabString);

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
              const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<SpriteArgs> &args);

    void addSprite(const std::shared_ptr<Sprite> &sprite, glm::vec2 position, glm::vec2 size);
};

}

#endif //PIXELGUI_SPRITECOMPOSITE_H
