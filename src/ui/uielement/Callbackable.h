//
// Created by Thijs on 07/05/2023.
//

#ifndef PIXELGUI_CALLBACKABLE_H
#define PIXELGUI_CALLBACKABLE_H

#include <functional>

#include "UIElement.h"

namespace PG {

class Callbackable {
public:

protected:
    void (* callbackFunc)(const std::shared_ptr<UIElement> &button) = emptyCallback;

    static void emptyCallback(const std::shared_ptr<UIElement> &uiElement) {
        (void) uiElement;
        DebugPrinter::print(DebugPrinter::DEBUG_MOUSE_BUTTON_UIELEMENT, "Callback:       ", uiElement, " (Empty)");
        throw std::bad_function_call();
    };

public:
    /// Set function that can be called.
    void setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &button));
};

}

#endif //PIXELGUI_CALLBACKABLE_H
