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
    SpriteComposite spriteComposite;

public:
    explicit MultiSprite(std::string textureName)
          : Sprite(std::move(textureName), glm::vec3(1.0f), 1.0f) {}

    MultiSprite(std::string textureName, glm::vec3 color, float alpha)
          : Sprite(std::move(textureName), color, alpha) {}

    explicit MultiSprite(SpriteComposite spriteComposite)
          : Sprite(""), spriteComposite(spriteComposite) {}

};

}

#endif //PIXELGUI_MULTISPRITE_H
