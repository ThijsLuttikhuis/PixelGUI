//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_SCENE_H
#define PIXELGUI_SCENE_H

#include "UIElement.h"

namespace PG {

class Scene : public UIElement {
private:
    std::vector<std::shared_ptr<UIElement>> uiElements;

public:
    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size)
          : UIElement(std::move(name), position, size, -1) {}

    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::unique_ptr<Sprite> sprite)
          : UIElement(std::move(name), position, size, std::move(sprite), -1) {}

    void onClick(glm::vec2 relativePos) override;

    void onHover(glm::vec2 relativePos) override;

    void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) override;
};

}

#endif //PIXELGUI_SCENE_H
