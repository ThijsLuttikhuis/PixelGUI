//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_UIEDITOR_H
#define PIXELGUI_UIEDITOR_H

#include "window/Window.h"
#include "ui/uielement/DraggableButton.h"

namespace PG {

class UIEditor : public std::enable_shared_from_this<UIEditor> {
private:
    std::shared_ptr<Window> window;

    int frameCounter = 0;
public:
    UIEditor();

    void initialize();

    void run();

    static void makeDraggableButtonCopyOnClick(const std::shared_ptr<UIElement> &button);

    [[nodiscard]] std::shared_ptr<UIEditor> getSharedFromThis();

    static void sayHi(const std::shared_ptr<UIElement> &uiElement);

    static void sliderChangeColor(const std::shared_ptr<UIElement> &uiElement);

    static void deleteOnReleaseIfLeftPanel(const std::shared_ptr<UIElement> &uiElement);

    static void setIntTextInput(const std::shared_ptr<UIElement> &uiElement);
};

}

#endif //PIXELGUI_UIEDITOR_H
