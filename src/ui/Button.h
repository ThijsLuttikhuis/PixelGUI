//
// Created by thijs on 5-1-23.
//

#ifndef PIXELGUI_BUTTON_H
#define PIXELGUI_BUTTON_H

#include <functional>
#include "UIElement.h"
#include "GLFW/glfw3.h"
#include "utilities/DebugPrinter.h"

namespace PG {

class Button : virtual public UIElement {
private:

    void (* callbackFunc)() = emptyCallback;

    static void emptyCallback() {
        DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Callback:       Empty");
        throw std::bad_function_call();
    };
public:


    void setCallbackFunction(void (* func)());

    void onClick(glm::vec2 relativePos) override;

};

}

#endif //PIXELGUI_BUTTON_H
