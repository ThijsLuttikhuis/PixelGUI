//
// Created by Thijs on 13/10/2023.
//

#ifndef PIXELGUI_EXTENDEDSCENE_H
#define PIXELGUI_EXTENDEDSCENE_H

#include "Scene.h"
#include "Slider.h"

namespace PG {

class ExtendedScene : public Scene, public Slider<int> {
public:
    ExtendedScene(std::string name, const glm::vec2 &position_, const glm::vec2 &size)
    : Scene(std::move(name), position_, size) {
        setBoundObjectsInBox(false);
    }

    ExtendedScene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite)
    : Scene(std::move(name), position, size, std::move(sprite)) {
        setBoundObjectsInBox(false);
    }

private:
    glm::vec2 extendedSize{};
    glm::vec2 currentViewPos{};

protected:
    bool sceneDragging = false;

public:
    void onClick(glm::vec2 mousePos) override;

    void onRelease(glm::vec2 mousePos) override;

    void onHover(glm::vec2 mousePos) override;

    void onKeyboardKey(int key, int action, int scanCode, const std::unique_ptr<std::vector<bool>> &keysPressed) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer, const std::unique_ptr<TextRenderer> &textRenderer,
              float baseZIndex) override;
};

} // PG

#endif //PIXELGUI_EXTENDEDSCENE_H
