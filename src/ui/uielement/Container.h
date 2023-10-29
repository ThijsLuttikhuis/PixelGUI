//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_CONTAINER_H
#define PIXELGUI_CONTAINER_H

#include "UIElement.h"

namespace PG {

class Scene;

class Container : virtual public UIElement {
public:
    Container(std::string name, const glm::vec2 &position_, const glm::vec2 &size)
          : UIElement(std::move(name), position_, size) {}

    Container(std::string name, const glm::vec2 &position, const glm::vec2 &size,
              std::shared_ptr<Sprite> sprite)
          : UIElement(std::move(name), position, size, std::move(sprite)) {}

private:
    glm::vec2 globalPosition{};

protected:
    std::vector<std::shared_ptr<UIElement>> children;

    /// Get index of uiElement in children
    [[nodiscard]] int getChildIndex(const std::shared_ptr<UIElement> &uiElement);

public:
    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
              const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) override;

    void onRelease(glm::vec2 mousePos) override;

    void onClick(glm::vec2 mousePos) override;

    void onHover(glm::vec2 mousePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onKeyboardKey(int key, int action, int scanCode,
                       const std::unique_ptr<std::vector<bool>> &keysPressed) override;

    void setParent(std::weak_ptr<Scene> parent_) override;

    void setGlobalPosition(glm::vec2 globalPosition_);

    void setGlobalPosition(int left, int up);

    void setPosition(glm::vec2 position_) override;

    void setPosition(int left, int up) override;

    void setPosition(glm::vec2 position_, pgu::positionAnchor anchor) override;

    void setPosition(int left, int up, pgu::positionAnchor anchor) override;

    /// Get children.
    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getChildren();

    glm::vec2 getGlobalPosition() const;
};

}

#endif //PIXELGUI_CONTAINER_H
