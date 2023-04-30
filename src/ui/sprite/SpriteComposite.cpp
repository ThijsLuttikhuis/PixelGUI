//
// Created by Thijs on 15/04/2023.
//

#include "SpriteComposite.h"

namespace PG {

SpriteComposite::SpriteComposite(const std::string &prefabString) {
    if (prefabString.starts_with("rectangle:")) {
        prefabRectangle(prefabString);
    }
}

void SpriteComposite::prefabRectangle(const std::string &prefabString) {
    auto sizeStrI = prefabString.find("size:");
    auto edgeColorStrI = prefabString.find("edgeColor:");
    auto fillColorStrI = prefabString.find("fillColor");
}

void SpriteComposite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
          const glm::vec2 &position, const glm::vec2 &size, const SpriteArgs &args) {

    for (unsigned long i = 0; i < sprites.size(); i++) {
        spriteRenderer->drawSprite(sprites[i], positions[i] + position, sizes[i], args);
    }
}

}
