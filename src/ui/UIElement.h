//
// Created by thijs on 13-06-22.
//

#ifndef PIXELGUI_UIELEMENT_H
#define PIXELGUI_UIELEMENT_H

#include <utility>
#include <string>
#include <glm/vec3.hpp>

#include "game/GameObject.h"
#include "Sprite.h"
#include "window/render/TextRenderer.h"
#include "window/render/SpriteRenderer.h"

namespace PG {

class UIElement {
private:
    static int uniqueIDCounter;
    int uniqueID;

    std::string name{};
protected:
    glm::vec2 position{};
    glm::vec2 size{};
    std::unique_ptr<Sprite> sprite{};

    bool enabled = true;
    bool visible = true;

    [[nodiscard]] bool isPositionInBox(double x, double y) const;

    static bool isPositionInBox(double x, double y, glm::vec2 pos, glm::vec2 size);

public:
    UIElement() {
        uniqueID = uniqueIDCounter++;
    }

    explicit UIElement(std::string name) : name(std::move(name)) {
        uniqueID = uniqueIDCounter++;
    }

    UIElement(std::string name, const glm::vec2 &position, const glm::vec2 &size)
          : name(std::move(name)), position(position), size(size) {
        uniqueID = uniqueIDCounter++;
    }

    UIElement(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::unique_ptr<Sprite> sprite)
          : name(std::move(name)), position(position), size(size), sprite(std::move(sprite)) {
        uniqueID = uniqueIDCounter++;
    }

    virtual ~UIElement() = default;

    bool operator ==(const UIElement &other) const {
        return uniqueID == other.uniqueID;
    }

    /// functions
    virtual void onHover(glm::vec2 relativePos);

    virtual void onClick(glm::vec2 relativePos);

    /// render
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) const;

    /// setters
    void forceSetUniqueID(int uniqueID_);

    void setPosition(glm::vec2 position_);

    void setPosition(int left, int up);

    void setSize(glm::vec2 size);

    void setSize(int width, int height);

    void setColor(const glm::vec3 &color_);

    void setAlpha(float alpha_);

    /// getters
    [[nodiscard]] int getUniqueID() const;

    [[nodiscard]] const glm::vec2 &getPosition() const;

    [[nodiscard]] const glm::vec2 &getSize() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] virtual bool isMouseHovering(double xPos, double yPos) const;

    [[nodiscard]] const std::unique_ptr<Sprite> &getSprite() const;

};

}


#endif //PIXELGUI_UIELEMENT_H
