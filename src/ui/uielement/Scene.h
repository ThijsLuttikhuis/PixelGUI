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

public:
    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size)
          : UIElement(std::move(name), position, size) {}

    Scene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite)
          : UIElement(std::move(name), position, size, std::move(sprite)) {}

    void onClick(glm::vec2 relativePos) override;

    void onHover(glm::vec2 mousePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void setDraggingChildPtr(const std::shared_ptr<UIElement> &uiElement);

    /// Find child the mouse is dragging over and set draggingChildPtr to that child.
    bool updateDraggingChild(glm::vec2 &relativeToScenePos, glm::vec2 &relativeToSceneDragStartPos);

    void setBoundObjectsInBox(bool boundObjects);

    void setChangeOwnerMode(enum changeOwnerMode changeOwner_);

    virtual void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    virtual void removeUIElement(const std::shared_ptr<UIElement> &uiElement);

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
              const std::unique_ptr<TextRenderer> &textRenderer) override;

    void onRelease(glm::vec2 mousePos) override;

    /**
     * Change owner of UIElement from (this) to a different Scene.
     *
     * @param[in] uiElementToChange UIElement (shared_ptr) to change the owner of.
     * @param[in] newOwner Scene (shared_ptr) the new owner for <B>UIElementToChange</B>.
     * @return[out] <B>true</B> if owner was changed successfully, else <B>false</B>.
     */
    bool changeOwner(const std::shared_ptr<UIElement>& uiElementToChange, const std::shared_ptr<Scene>& newOwner);


    /// Get children of parent.
    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getSiblings();

    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getChildren();

    [[nodiscard]] int getChildIndex(const std::shared_ptr<UIElement> &uiElement);

    [[nodiscard]] enum changeOwnerMode getChangeOwnerMode() const;

    bool updateOwnerChange(const std::shared_ptr<UIElement> &draggingChild, const glm::vec2 &draggingChildPos);
};

}

#endif //PIXELGUI_SCENE_H
