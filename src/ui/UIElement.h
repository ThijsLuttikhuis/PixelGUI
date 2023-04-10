//
// Created by thijs on 13-06-22.
//

#ifndef PIXELGUI_UIELEMENT_H
#define PIXELGUI_UIELEMENT_H

#include <utility>
#include <string>
#include <glm/vec3.hpp>

#include "Sprite.h"
#include "window/render/TextRenderer.h"
#include "window/render/SpriteRenderer.h"
#include "GLFW/glfw3.h"

namespace PG {

class UIElement : public std::enable_shared_from_this<UIElement> {
private:
    static int uniqueIDCounter;
    int uniqueID;

    std::string name{};
protected:
    std::weak_ptr<UIElement> parent;

    glm::vec2 position{};
    glm::vec2 size{};
    std::unique_ptr<Sprite> sprite{};

    int keyboardKey = GLFW_KEY_UNKNOWN;

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

    UIElement(std::string name, const glm::vec2 &position, const glm::vec2 &size, int keyboardKey = GLFW_KEY_UNKNOWN)
          : name(std::move(name)), position(position), size(size), keyboardKey(keyboardKey) {
        uniqueID = uniqueIDCounter++;
    }

    UIElement(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::unique_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : name(std::move(name)), position(position), size(size), sprite(std::move(sprite)), keyboardKey(keyboardKey) {
        uniqueID = uniqueIDCounter++;
    }

    virtual ~UIElement() = default;

    bool operator ==(const UIElement &other) const {
        return uniqueID == other.uniqueID;
    }

    /// functions
    virtual void onHover(glm::vec2 mousePos);

    virtual void onClick(glm::vec2 mousePos);

    virtual void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos);

    /// render
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer);

    /// setters
    void forceSetUniqueID(int uniqueID_);

    void setParent(std::weak_ptr<UIElement> parent_);

    void setPosition(glm::vec2 position_);

    void setPosition(int left, int up);

    void setSize(glm::vec2 size);

    void setSize(int width, int height);

    void setColor(const glm::vec3 &color_);

    void setAlpha(float alpha_);

    void setVisibility(bool visible_);

    void setEnabled(bool enabled_);

    void enable();

    void disable();

    void hide();

    void show();

    /// getters
    [[nodiscard]] std::shared_ptr<UIElement> getSharedFromThis();

    [[nodiscard]] int getUniqueID() const;

    [[nodiscard]] const glm::vec2 &getPosition() const;

    [[nodiscard]] const glm::vec2 &getSize() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] virtual bool isMouseHovering(double xPos, double yPos) const;

    [[nodiscard]] virtual bool isMouseHovering(const glm::vec2 &pos) const;

    [[nodiscard]] const std::unique_ptr<Sprite> &getSprite() const;

    [[nodiscard]] bool isPressed(double xPos, double yPos) const;

    [[nodiscard]] bool isKeyPressed(int key) const;

    [[nodiscard]] bool isEnabled() const;

    [[nodiscard]] bool isVisible() const;

    [[nodiscard]] bool isHidden() const;

};

}

#endif //PIXELGUI_UIELEMENT_H
