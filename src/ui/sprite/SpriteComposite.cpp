//
// Created by Thijs on 15/04/2023.
//

#include "SpriteComposite.h"

namespace PG {

void SpriteComposite::addSprite(const std::shared_ptr<Sprite> &sprite, glm::vec2 position, glm::vec2 size) {
    sprites.push_back(sprite);
    positions.push_back(position);
    sizes.push_back(size);
}

void SpriteComposite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                           const std::unique_ptr<TextRenderer> &textRenderer,
                           const std::shared_ptr<Sprite> &referenceSprite,
                           const glm::vec2 &position, const glm::vec2 &size, float baseZIndex) {

    (void) size;
    for (unsigned long i = 0; i < sprites.size(); i++) {
        sprites[i]->setBlendColor(referenceSprite->getBlendColor());
        sprites[i]->draw(spriteRenderer, textRenderer, positions[i] + position, sizes[i], baseZIndex);
    }
}

const std::vector<std::shared_ptr<Sprite>> &SpriteComposite::getSprites() const {
    return sprites;
}

}
