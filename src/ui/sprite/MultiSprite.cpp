//
// Created by Thijs on 15/04/2023.
//

#include "MultiSprite.h"

namespace PG {

    void MultiSprite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
                           const glm::vec2 &position,
                           const glm::vec2 &size, const SpriteArgs &args) {


        spriteComposite->draw(spriteRenderer, textRenderer, position, size, args);
    }
}