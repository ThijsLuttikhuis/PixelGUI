//
// Created by Thijs on 21/06/2023.
//

#include "ui/sprite/RectangleSpriteComposite.h"

#include "DraggableButtonResizable.h"

namespace PG {

DraggableButtonResizable::DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                                                   std::shared_ptr<Sprite> sprite, int keyboardKey)
      : UIElement(std::move(name), pos, size, std::move(sprite), keyboardKey) {

    customMouse = std::make_shared<CustomMouseSprite>("mouseresizehover");
    setEdgeSprite(5, {1, 0, 0, 0.5}, {1, 1, 1, 0});
    setMinValue(1);
    setMaxValue(INT_MAX);
    Slider<int>::setCallbackFunction(sliderUpdateUIElementSize);
}

DraggableButtonResizable::DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                                                   int keyboardKey)
      : UIElement(std::move(name), pos, size, keyboardKey) {

    customMouse = std::make_shared<CustomMouseSprite>("mouseresizehover");
    setEdgeSprite(5, {1, 0, 0, 0.5}, {1, 1, 1, 0});
    setMinValue(1);
    setMaxValue(INT_MAX);
    Slider<int>::setCallbackFunction(sliderUpdateUIElementSize);
}

void DraggableButtonResizable::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (resizing) {
        dragging = true;

        Slider<int>::onDrag(mousePos, dragStartPos);

    } else {
        DraggableButton::onDrag(mousePos, dragStartPos);
    }
}

void DraggableButtonResizable::onRelease(glm::vec2 mousePos) {

    if (!dragging) {
        // if mouse is on the edge of the button, switch to resizing mode
        resizing = isPositionOnEdge(mousePos);
    } else {
        try {
            Button::callbackFunc(getSharedFromThis());
        }
        catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
    }
}

void DraggableButtonResizable::onClick(glm::vec2 mousePos) {
    (void) mousePos;
    resizing &= isPositionOnEdge(mousePos);

    pressed = true;
    dragging = false;
}

void DraggableButtonResizable::onHover(glm::vec2 mousePos) {
    if (resizing && isPositionOnEdge(mousePos)) {
        customMouse->setMouse();
    }
    if (resizing) {
        drawEdgeSprite = true;
    }
    if (isPositionOnEdge(mousePos)) {
        //TODO: set slide direction based on mouse position
        setSlideDirection({1, 0});
        setValue(static_cast<int>(getSize().x));

        drawEdgeSprite = true;
    }
}

bool DraggableButtonResizable::isPositionOnEdge(glm::vec2 mousePos) {
    return isMouseHovering(mousePos) && !isPositionInBox(mousePos.x, mousePos.y, edgeSize);
}

std::shared_ptr<CustomMouseSprite> &DraggableButtonResizable::getCustomMouse() {
    return customMouse;
}

void DraggableButtonResizable::setParent(std::weak_ptr<Scene> parent_) {
    UIElement::setParent(parent_);
    if (customMouse) {
        customMouse->setRootScene(getRootScene());
    }
}

void DraggableButtonResizable::setCustomMouse(const std::shared_ptr<CustomMouseSprite> &customMouse_) {
    customMouse = customMouse_;
    if (hasParent()) {
        customMouse->setRootScene(getRootScene());
    }
}

void DraggableButtonResizable::setEdgeSprite(const std::shared_ptr<Sprite> &edgeSprite_) {
    edgeSprite = edgeSprite_;
}

void DraggableButtonResizable::setEdgeSprite(int edgeSize_, glm::vec4 edgeColor, glm::vec4 fillColor) {
    edgeSize = edgeSize_;
    edgeSprite = std::make_shared<MultiSprite>(
          std::make_shared<RectangleSpriteComposite>(getSize(), edgeSize, edgeColor, fillColor));
}

void DraggableButtonResizable::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                                    const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {
    UIElement::draw(spriteRenderer, textRenderer, baseZIndex);
    if (drawEdgeSprite && edgeSprite) {
        edgeSprite->draw(spriteRenderer, textRenderer, getPosition(), getSize(), baseZIndex);
    }
    drawEdgeSprite = false;

}

void DraggableButtonResizable::sliderUpdateUIElementSize(const std::shared_ptr<UIElement> &uiElement) {
    auto slider = std::dynamic_pointer_cast<DraggableButtonResizable>(uiElement);
    auto sliderValue = slider->getValue();
    auto sliderSize = slider->getSize();
    slider->setSize(sliderValue, static_cast<int>(sliderSize.y));
    slider->setEdgeSprite(5, {1, 0, 0, 0.5}, {1, 1, 1, 0});
}

} // PG
