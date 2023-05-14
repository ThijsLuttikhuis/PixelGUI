//
// Created by thijs on 13-06-22.
//

#ifndef PIXELGUI_UIELEMENT_H
#define PIXELGUI_UIELEMENT_H

#include <utility>
#include <string>
#include "glm-0.9.7.1/glm/vec3.hpp"

#include "ui/sprite/Sprite.h"
#include "window/render/TextRenderer.h"
#include "window/render/SpriteRenderer.h"
#include "GLFW/glfw3.h"
#include "utilities/DebugPrinter.h"
#include "utilities/pgu.h"

namespace PG {

class Scene;

class UIElement : public std::enable_shared_from_this<UIElement> {
private:
    static int uniqueIDCounter;
    int uniqueID;

    std::string name{};

protected:
    std::weak_ptr<Scene> parentPtr;

    glm::vec2 position{};
    glm::vec2 size{};
    std::shared_ptr<Sprite> sprite{};

    int keyboardKey = GLFW_KEY_UNKNOWN;

    bool enabled = true;
    bool visible = true;

    /// Get if position is within the bounding box of this UIElement.
    [[nodiscard]] bool isPositionInBox(double x, double y) const;

    /// Get if position is within the bounding box of {pos, size}.
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

    UIElement(std::string name, const glm::vec2 &position, const glm::vec2 &size,
              std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : name(std::move(name)), position(position), size(size), sprite(std::move(sprite)), keyboardKey(keyboardKey) {
        uniqueID = uniqueIDCounter++;
    }

    virtual ~UIElement() = default;

    /// Check if two UIElements are the same based on their unique identifier.
    bool operator ==(const UIElement &other) const {
        return uniqueID == other.uniqueID;
    }

    [[nodiscard]] std::shared_ptr<UIElement> getSharedFromThis();

    /// Called when hovering on the UIElement.
    virtual void onHover(glm::vec2 mousePos);

    /// Called when mouse down on the UIElement.
    virtual void onClick(glm::vec2 mousePos);

    /// Called when mouse up on the UIElement.
    virtual void onRelease(glm::vec2 mousePos);

    /// Called when hovering on the UIElement while clicking.
    virtual void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos);

    /// Draw the UIElement according to the sprite it contains.
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex);

    /// Force set unique identifier of UIElement.
    void forceSetUniqueID(int uniqueID_);

    /// Set parent of UIElement, which must be a Scene.
    void setParent(std::weak_ptr<Scene> parent_);

    /// Set position of UIElement.
    void setPosition(glm::vec2 position_);

    /// Set position of UIElement.
    void setPosition(int left, int up);

    /// Set size of UIElement.
    void setSize(glm::vec2 size_);

    /// Set size of UIElement.
    void setSize(int width, int height);

    /// Set color of UIElement.
    void setColor(const glm::vec3 &color_);

    /// Set alpha channel of color of UIElement.
    void setAlpha(float alpha_);

    /// Set visibility of UIElement.
    void setVisibility(bool visible_);

    /// Set if content of UIElement is enabled.
    void setEnabled(bool enabled_);

    /// Set enabled to true.
    void enable();

    /// Set enabled to false.
    void disable();

    /// Set visibility to true.
    void show();

    /// Set visibility to false.
    void hide();

    /// Get unique identifier of UIElement.
    [[nodiscard]] int getUniqueID() const;

    /// Get parent of UIElement, which must be a Scene.
    [[nodiscard]] std::weak_ptr<Scene> getParent() const;

    /// Get if UIElement has a parent.
    [[nodiscard]] bool hasParent() const;

    /// Get if position is hovering over UIElement.
    [[nodiscard]] virtual bool isMouseHovering(double xPos, double yPos) const;

    /// Get if position is hovering over UIElement.
    [[nodiscard]] virtual bool isMouseHovering(const glm::vec2 &pos) const;

    /// Get position of UIElement.
    [[nodiscard]] const glm::vec2 &getPosition() const;

    /// Get size of UIElement.
    [[nodiscard]] const glm::vec2 &getSize() const;

    /// Get name of UIElement.
    [[nodiscard]] const std::string &getName() const;

    /// Get sprite of UIElement.
    [[nodiscard]] const std::shared_ptr<Sprite> &getSprite() const;

    /// Get if position is hovering over UIElement and UIElement is enabled.
    [[nodiscard]] bool isPressed(double xPos, double yPos) const;

    /// Get if keyboardKey is the same as key.
    [[nodiscard]] bool isKeyPressed(int key) const;

    /// Get if enabled is true.
    [[nodiscard]] bool isEnabled() const;

    /// Get if visible is true.
    [[nodiscard]] bool isVisible() const;

    /// Get if visible is false.
    [[nodiscard]] bool isHidden() const;
};

}

#endif //PIXELGUI_UIELEMENT_H
