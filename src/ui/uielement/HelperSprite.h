//
// Created by Thijs on 10/07/2023.
//

#ifndef PIXELGUI_HELPERSPRITE_H
#define PIXELGUI_HELPERSPRITE_H

#include "ui/sprite/Sprite.h"
#include "ui/uielement/UIElement.h"

namespace PG {

class HelperSprite : virtual public UIElement {
protected:
    std::shared_ptr<Sprite> helperSprite = std::make_shared<Sprite>("mouseselecthover");

public:
    void setHelperSprite(std::shared_ptr<Sprite> sprite) {
        helperSprite = std::move(sprite);
    }

    [[nodiscard]] const std::shared_ptr<Sprite> &getHelperSprite() const {
        return helperSprite;
    }
};

} // PG

#endif //PIXELGUI_HELPERSPRITE_H
