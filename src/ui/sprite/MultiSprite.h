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
    explicit MultiSprite(std::shared_ptr<SpriteComposite> spriteComposite, float alpha = 1.0f)
          : Sprite("", glm::vec3(1.0f), alpha), spriteComposite(std::move(spriteComposite)) {}

    static std::shared_ptr<SpriteComposite> getSpriteCompositeFromString(const std::string &prefabString);

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
                      const glm::vec2 &position, const glm::vec2 &size, float baseZIndex) override;

};

}

#endif //PIXELGUI_MULTISPRITE_H
