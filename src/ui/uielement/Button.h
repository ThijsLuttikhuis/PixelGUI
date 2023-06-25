//
// Created by thijs on 5-1-23.
//

#ifndef PIXELGUI_BUTTON_H
#define PIXELGUI_BUTTON_H

#include <functional>
#include "UIElement.h"
#include "GLFW/glfw3.h"
#include "utilities/DebugPrinter.h"
#include "Callbackable.h"

namespace PG {

class Button : virtual public UIElement, virtual public Callbackable {
protected:
    Button() = default;
public:

};


} // PG

#endif //PIXELGUI_BUTTON_H
