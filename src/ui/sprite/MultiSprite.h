//
// Created by Thijs on 15/04/2023.
//

#ifndef PIXELGUI_MULTISPRITE_H
#define PIXELGUI_MULTISPRITE_H

#include "Sprite.h"

#include <utility>
#include "SpriteComposite.h"

namespace PG {

class MultiSprite : public Sprite {
private:
    std::shared_ptr<SpriteComposite> spriteComposite;

public:
    explicit MultiSprite(std::shared_ptr<SpriteComposite> spriteComposite,
                         glm::vec3 color = glm::vec3(1.0f), float alpha = 1.0f)
          : Sprite("", color, alpha), spriteComposite(std::move(spriteComposite)) {}

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
                      const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<SpriteArgs> &args) override;

};

}

#endif //PIXELGUI_MULTISPRITE_H
