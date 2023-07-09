//
// Created by Thijs on 02/07/2023.
//

#ifndef PIXELGUI_CUSTOMMOUSE_H
#define PIXELGUI_CUSTOMMOUSE_H

#include <memory>
#include "ui/uielement/UIElement.h"

namespace PG {

class CustomMouse : virtual public UIElement {
private:
    std::shared_ptr<Sprite> customSprite;

public:



};

} // PG

#endif //PIXELGUI_CUSTOMMOUSE_H
