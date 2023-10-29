//
// Created by Thijs on 15/10/2023.
//

#ifndef PIXELGUI_SCENE_H
#define PIXELGUI_SCENE_H

#include "Container.h"

namespace PG {

class Scene : public Container {
public:
    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite)
    : Container(std::move(name), position, size, std::move(sprite)) {}

    Scene(std::string name, const glm::vec2 &position_, const glm::vec2 &size)
    : Container(std::move(name), position_, size) {}

    enum changeOwnerMode {
        alwaysAllowOwnerChange,
        noOwnerChange,
        onlyReceiveUIElements,
        onlyGiveUIElements
    };
private:
    bool boundObjectsInBox = true;

    changeOwnerMode changeOwnerMode = noOwnerChange;

    std::weak_ptr<UIElement> draggingChildPtr = std::weak_ptr<UIElement>();
    std::weak_ptr<UIElement> textInputChildPtr = std::weak_ptr<UIElement>();

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

    /// Remove uiElement from children based in index.
    void removeUIElement(int index);
public:
    /// Add UIElement to children.
    virtual void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    /// Remove UIElement from children.
    virtual void removeUIElement(const std::shared_ptr<UIElement> &uiElement);

    void onRelease(glm::vec2 mousePos) override;

    void onClick(glm::vec2 mousePos) override;

    void onHover(glm::vec2 mousePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onKeyboardKey(int key, int action, int scanCode,
                       const std::unique_ptr<std::vector<bool>> &keysPressed) override;

    /// Set the child the uiElement is currently dragging on.
    void setDraggingChild(const std::weak_ptr<UIElement> &uiElement);

    void clearDraggingChild();

    /// Set if objects are allowed to leave the Container.
    void setBoundObjectsInBox(bool boundObjects);

    /// Set the child which is currently receiving text input
    void setTextInputChild(const std::weak_ptr<UIElement> &uiElement);

    void clearTextInputChild();

    /// Set policy on owner change.
    void setChangeOwnerMode(enum changeOwnerMode changeOwner_);

    /// Get the child the uiElement is currently dragging on.
    [[nodiscard]] std::shared_ptr<UIElement> getDraggingChild();

    /// Get the child which is currently receiving text input.
    [[nodiscard]] std::shared_ptr<UIElement> getTextInputChild();

    /// Get policy on owner change.
    [[nodiscard]] enum changeOwnerMode getChangeOwnerMode() const;

    /// Get children of parent.
    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getSiblings();
};

} // PG

#endif //PIXELGUI_SCENE_H
