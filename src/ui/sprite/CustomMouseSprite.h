//
// Created by Thijs on 02/07/2023.
//

#ifndef PIXELGUI_CUSTOMMOUSESPRITE_H
#define PIXELGUI_CUSTOMMOUSESPRITE_H

#include <memory>
#include <utility>
#include "ui/uielement/UIElement.h"
#include "ui/uielement/HelperSprite.h"
#include "ui/uielement/PositionAnchor.h"

namespace PG {

class CustomMouseSprite : public Sprite {
private:
    std::shared_ptr<PositionAnchor> positionAnchor;
    std::shared_ptr<RootScene> rootScene{};
public:
    explicit CustomMouseSprite(std::string textureName = "mouseselecthover", std::shared_ptr<PositionAnchor> positionAnchor = std::make_shared<AnchorMiddle>())
          : Sprite(std::move(textureName)), positionAnchor(std::move(positionAnchor)) {}

    CustomMouseSprite(std::string textureName, std::shared_ptr<PositionAnchor> positionAnchor, std::shared_ptr<RootScene> &rootScene)
          : Sprite(std::move(textureName)), positionAnchor(std::move(positionAnchor)), rootScene(rootScene) {}

    void setMouse();

    void setRootScene(std::shared_ptr<RootScene> rootScene_);
};

} // PG

#endif //PIXELGUI_CUSTOMMOUSESPRITE_H
