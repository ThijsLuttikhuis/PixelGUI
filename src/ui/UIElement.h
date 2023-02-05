//
// Created by thijs on 13-06-22.
//

#ifndef PIXELGUI_UIELEMENT_H
#define PIXELGUI_UIELEMENT_H

#include <string>

#include "game/GameObject.h"
#include "Sprite.h"

namespace PG {

class UIElement : public GameObject {
protected:
    std::unique_ptr<Sprite> sprite;

    [[nodiscard]] bool isPositionInBox(double x, double y) const;

    static bool isPositionInBox(double x, double y, glm::vec2 pos, glm::vec2 size);

public:
    UIElement(std::string name, const glm::vec2 &pos, const glm::vec2 &size)
          : GameObject(std::move(name), pos, size) {}

    UIElement(std::string name, const glm::vec2 &pos, const glm::vec2 &size, std::unique_ptr<Sprite> sprite)
          : GameObject(std::move(name), pos, size), sprite(std::move(sprite)) {}

    /// render
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) const;

    /// setters
    void setColor(const glm::vec3 &color_);

    void setAlpha(float alpha_);

    /// getters
    [[nodiscard]] virtual bool isMouseHovering(double xPos, double yPos) const;

    [[nodiscard]] const std::unique_ptr<Sprite> &getSprite() const;

};

}


#endif //PIXELGUI_UIELEMENT_H
