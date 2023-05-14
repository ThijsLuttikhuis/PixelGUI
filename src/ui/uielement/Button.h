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
public:
    enum pressMode {
        pressOnClick,
        pressOnRelease,
        pressOnReleaseAfterDrag,
        isDraggingForPressOnReleaseAfterDrag, // used to check dragging for pressOnReleaseAfterDrag
    };
private:
    pressMode pressMode = pressOnReleaseAfterDrag;

public:
    Button() : UIElement() {};

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size,
           int keyboardKey = GLFW_KEY_UNKNOWN, enum pressMode pressMode = pressOnReleaseAfterDrag)
          : UIElement(std::move(name), position, size, keyboardKey), pressMode(pressMode) {}

    Button(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
           int keyboardKey = GLFW_KEY_UNKNOWN, enum pressMode pressMode = pressOnReleaseAfterDrag)
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey),
            pressMode(pressMode) {}

    void onClick(glm::vec2 relativePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onRelease(glm::vec2 mousePos) override;

    /// Set when the button will be pressed.
    void setPressMode(enum pressMode pressMode);

    /// Get when the button will be pressed.
    [[nodiscard]] enum pressMode getPressMode();

};


}

#endif //PIXELGUI_BUTTON_H
