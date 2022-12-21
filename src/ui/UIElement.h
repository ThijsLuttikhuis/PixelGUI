//
// Created by thijs on 13-06-22.
//

#ifndef DICEGONEROGUE_UIELEMENT_H
#define DICEGONEROGUE_UIELEMENT_H

#include <string>

#include "game/GameObject.h"

namespace PG {

class UIElement : public GameObject {
protected:
    glm::vec3 color;
    float alpha;
    bool mouseIsHovering = false;

    bool isPositionInBox(double x, double y);

    static bool isPositionInBox(double x, double y, glm::vec2 pos, glm::vec2 size);

public:
    UIElement(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
              const glm::vec3 &color = glm::vec3(0.0f), float alpha = 1.0f)
          : GameObject(std::move(name), pos, size), color(color), alpha(alpha) {}

    /// render
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) const;

    /// setters
    void setColor(const glm::vec3 &color_);

    void setIsMouseHovering(bool hover);

    /// getters
    [[nodiscard]] virtual bool isMouseHovering(double xPos, double yPos) const;

    [[nodiscard]] bool isMouseHovering() const;
};

}


#endif //DICEGONEROGUE_UIELEMENT_H
