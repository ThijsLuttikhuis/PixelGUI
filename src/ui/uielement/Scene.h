//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_SCENE_H
#define PIXELGUI_SCENE_H

#include "UIElement.h"

namespace PG {

class Scene : public UIElement {
protected:
    std::vector<std::shared_ptr<UIElement>> children;

    std::shared_ptr<UIElement> selectedChild = nullptr;

public:
    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size)
          : UIElement(std::move(name), position, size) {}

    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite)
          : UIElement(std::move(name), position, size, std::move(sprite)) {}

    void onClick(glm::vec2 relativePos) override;

    void onHover(glm::vec2 relativePos) override;

    void onDrag(glm::vec2 relativePos, glm::vec2 dragStartPos) override;

    virtual void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) override;

};

}

#endif //PIXELGUI_SCENE_H