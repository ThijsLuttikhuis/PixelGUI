//
// Created by Thijs on 02/07/2023.
//

#ifndef PIXELGUI_CUSTOMMOUSE_H
#define PIXELGUI_CUSTOMMOUSE_H

#include <memory>
#include "ui/uielement/UIElement.h"
#include "HelperSprite.h"

namespace PG {

class CustomMouse : virtual public UIElement, public HelperSprite {
private:

public:


    void onHover(glm::vec2 mousePos) override;



};

} // PG

#endif //PIXELGUI_CUSTOMMOUSE_H
