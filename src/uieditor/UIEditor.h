//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_UIEDITOR_H
#define PIXELGUI_UIEDITOR_H

#include "window/Window.h"

namespace PG {

class UIEditor {
private:
    std::shared_ptr<Window> window;
public:
    UIEditor();

    void run();
};

}

#endif //PIXELGUI_UIEDITOR_H
