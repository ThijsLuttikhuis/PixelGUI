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
    customMouse->setPositionOffsetFactor({-0.5f, -0.5f});
    setEdgeSprite(5, {1, 0, 0, 0.5}, {1, 1, 1, 0});
    setMinValue(1);
    setMaxValue(INT_MAX);
    Slider<int>::setCallbackFunction(sliderUpdateUIElementSize);
    Slider<int>::setAllowLoopAroundOutOfScreen(false);
}

DraggableButtonResizable::DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                                                   int keyboardKey)
      : UIElement(std::move(name), pos, size, keyboardKey) {

    customMouse = std::make_shared<CustomMouseSprite>("mouseresizehover");
    customMouse->setPositionOffsetFactor({-0.5f, -0.5f});
    setEdgeSprite(5, {1, 0, 0, 0.5}, {1, 1, 1, 0});
    setMinValue(1);
    setMaxValue(INT_MAX);
    Slider<int>::setCallbackFunction(sliderUpdateUIElementSize);
    Slider<int>::setAllowLoopAroundOutOfScreen(false);
}

void DraggableButtonResizable::onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) {
    if (resizing) {

        Slider<int>::onDrag(mousePos, dragStartPos);

//        dragging = false;
    } else {
        DraggableButton::onDrag(mousePos, dragStartPos);
    }
}

void DraggableButtonResizable::onRelease(glm::vec2 mousePos) {

    if (!dragging) {
        // if mouse is on the edge of the button, switch to resizing mode
        resizing = static_cast<bool>(isPositionOnEdge(mousePos));

    } else {
        try {
            Button::callbackFunc(getSharedFromThis());
        }
        catch (const std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
    }
    dragging = false;
    lockSlideDir = false;

}

void DraggableButtonResizable::onClick(glm::vec2 mousePos) {
    (void) mousePos;
    resizing &= isPositionOnEdgeBool(mousePos);
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
    auto elementEdge = isPositionOnEdge(mousePos);
    if (elementEdge) {
        auto slideDir = elementEdge.toSlideDirection();
        slideDir = glm::normalize(slideDir * getSize());

        if (!lockSlideDir) {
            setSlideDirection(slideDir);
            std::cout << slideDir.x << "  set " << slideDir.y << std::endl;
        }
        setValue(static_cast<int>(slideDir.x != 0 ? getSize().x : getSize().y));
        resizingEdge = elementEdge;

        drawEdgeSprite = true;
    }
}

bool DraggableButtonResizable::isPositionOnEdgeBool(glm::vec2 mousePos) {
    return static_cast<bool>(isPositionOnEdge(mousePos));
}

DraggableButtonResizable::elementEdge DraggableButtonResizable::isPositionOnEdge(glm::vec2 mousePos) {
    bool isOnEdge = isMouseHovering(mousePos) && !isPositionInBox(mousePos.x, mousePos.y, edgeSize);

    auto whichEdge = elementEdge(elementEdge::edge::none);

    if (!isOnEdge) {
        return whichEdge;
    }
    auto pos = getPosition();
    auto size = getSize();

    bool isLeft = mousePos.x >= pos.x && mousePos.x < pos.x + edgeSize;
    bool isTop = mousePos.y >= pos.y && mousePos.y < pos.y + edgeSize;
    bool isRight = mousePos.x > pos.x + size.x - edgeSize && mousePos.x <= pos.x + size.x;
    bool isBottom = mousePos.y > pos.y + size.y - edgeSize && mousePos.y <= pos.y + size.y;

    whichEdge.edge = static_cast<enum elementEdge::edge>(isTop * (int) elementEdge::edge::top +
                                                         isLeft * (int) elementEdge::edge::left +
                                                         isRight * (int) elementEdge::edge::right +
                                                         isBottom * (int) elementEdge::edge::bottom);

    return whichEdge;
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

void DraggableButtonResizable::setEdgeSprite(float edgeSize_, glm::vec4 edgeColor, glm::vec4 fillColor) {
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
    auto sliderResizable = std::dynamic_pointer_cast<DraggableButtonResizable>(uiElement);
    sliderResizable->lockSlideDir = true;
    int sliderValue = sliderResizable->getValue();
    glm::vec2 sliderSize = sliderResizable->getSize();
    glm::vec2 slideDir = sliderResizable->getSlideDirection();

    glm::vec2 newSize = sliderSize;
    newSize.x = slideDir.x != 0 ? (float) sliderValue : sliderSize.x;
    newSize.y = slideDir.x != 0 && slideDir.y != 0 ? (float) sliderValue * slideDir.y / slideDir.x :
                slideDir.y != 0 ? (float) sliderValue : sliderSize.y;

    newSize = glm::abs(newSize);

    if (newSize.x < sliderResizable->edgeSize * 2) {
        newSize.x = sliderResizable->edgeSize * 2;
    }
    if (newSize.y < sliderResizable->edgeSize * 2) {
        newSize.y = sliderResizable->edgeSize * 2;
    }

    auto dSize = newSize - sliderSize;
    auto dNewPos = glm::vec2(slideDir.x < 0 ? -1 : 0,
                    slideDir.y < 0 ? -1 : 0);
    auto newPos = sliderResizable->getPosition() + dSize * dNewPos;

    sliderResizable->setSize(newSize);
    sliderResizable->setPosition(newPos);
    sliderResizable->setEdgeSprite(5, {1, 0, 0, 0.5}, {1, 1, 1, 0});
}

} // PG
