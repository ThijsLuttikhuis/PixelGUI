//
// Created by Thijs on 02/07/2023.
//

#ifndef PIXELGUI_CUSTOMMOUSESPRITE_H
#define PIXELGUI_CUSTOMMOUSESPRITE_H

#include <memory>
#include <utility>
#include "ui/uielement/UIElement.h"
#include "ui/uielement/HelperSprite.h"

namespace PG {

class CustomMouseSprite : public Sprite {
private:
    std::shared_ptr<RootScene> rootScene{};

    glm::vec2 positionOffsetFactor{};

public:
    explicit CustomMouseSprite(std::string textureName = "mouseselecthover")
          : Sprite(std::move(textureName)) {

        zIndex = 1.0f;
    }

    CustomMouseSprite(std::string textureName, std::shared_ptr<RootScene> &rootScene)
          : Sprite(std::move(textureName)), rootScene(rootScene) {

        zIndex = 1.0f;
    }

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer,
                      const glm::vec2 &position, const glm::vec2 &size,
                      float baseZIndex) override;

    void setMouse(float rotation = 0);

    void setRootScene(std::shared_ptr<RootScene> rootScene_);

    void  setPositionOffsetFactor(glm::vec2 offsetFactor);
};

} // PG

#endif //PIXELGUI_CUSTOMMOUSESPRITE_H
