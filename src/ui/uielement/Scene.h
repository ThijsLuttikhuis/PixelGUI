//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_SCENE_H
#define PIXELGUI_SCENE_H

#include "UIElement.h"

namespace PG {

class Scene : public UIElement {
public:
    enum changeOwnerMode {
        alwaysAllowOwnerChange,
        noOwnerChange,
        onlyReceiveUIElements,
        onlyGiveUIElements
    };
protected:
    bool boundObjectsInBox = true;

    changeOwnerMode changeOwnerMode = noOwnerChange;

    std::vector<std::shared_ptr<UIElement>> children;

    std::weak_ptr<UIElement> draggingChildPtr = std::weak_ptr<UIElement>();

    /// Get index of uiElement in children
    [[nodiscard]] int getChildIndex(const std::shared_ptr<UIElement> &uiElement);

    /// Remove uiElement from children based in index.
    void removeUIElement(int index);

private:
    /// Find child the mouse is dragging over and set draggingChildPtr to that child.
    bool updateDraggingChild(glm::vec2 &relativeToScenePos);

    /// Find child the mouse is dragging over and change owner if its position is outside of this scene.
    bool updateOwnerChange(const std::shared_ptr<UIElement> &draggingChild,
                           const glm::vec2 &mousePos, const glm::vec2 &dragStartPos);

    /**
     * Change owner of UIElement from (this) to a different Scene.
     *
     * @param[in] uiElementToChange UIElement (shared_ptr) to change the owner of.
     * @param[in] newOwner Scene (shared_ptr) the new owner for <B>UIElementToChange</B>.
     * @return[out] <B>true</B> if owner was changed successfully, else <B>false</B>.
     */
    bool changeOwner(const std::shared_ptr<UIElement> &uiElementToChange, const std::shared_ptr<Scene> &newOwner);

public:
    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size)
          : UIElement(std::move(name), position, size) {}

    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite)
          : UIElement(std::move(name), position, size, std::move(sprite)) {}

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
              const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) override;

    void onRelease(glm::vec2 mousePos) override;

    void onClick(glm::vec2 mousePos) override;

    void onHover(glm::vec2 mousePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    /// Add UIElement to children.
    virtual void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    /// Remove UIElement from children.
    virtual void removeUIElement(const std::shared_ptr<UIElement> &uiElement);

    /// Set the child the uiElement is currently dragging on.
    void setDraggingChildPtr(const std::shared_ptr<UIElement> &uiElement);

    /// Set if objects are allowed to leave the Scene.
    void setBoundObjectsInBox(bool boundObjects);

    /// Set policy on owner change.
    void setChangeOwnerMode(enum changeOwnerMode changeOwner_);

    /// Get children of parent.
    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getSiblings();

    /// Get children.
    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getChildren();

    /// Get policy on owner change.
    [[nodiscard]] enum changeOwnerMode getChangeOwnerMode() const;

};

}

#endif //PIXELGUI_SCENE_H
