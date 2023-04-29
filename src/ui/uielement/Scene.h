//
// Created by Thijs on 31/03/2023.
//

#ifndef PIXELGUI_SCENE_H
#define PIXELGUI_SCENE_H

#include "UIElement.h"

namespace PG {

class Scene : public UIElement {
protected:
    bool boundObjectsInBox = true;
    bool changeOwnerWhenDraggingOutsideScene = false;

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

    void setBoundObjectsInBox(bool boundObjects);

    void setChangeOwnerWhenDraggingOutsideScene(bool changeOwner);

    virtual void addUIElement(const std::shared_ptr<UIElement> &uiElement);

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
              const std::unique_ptr<TextRenderer> &textRenderer) override;

    void onRelease(glm::vec2 mousePos) override;

    bool changeOwner(const std::shared_ptr<UIElement>& uiElementToChange, const std::shared_ptr<Scene>& newOwner);

    [[nodiscard]] bool getChangeOwnerWhenDraggingOutsideScene() const;

    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getSiblings();

    [[nodiscard]] std::vector<std::shared_ptr<UIElement>> getChildren();
};

}

#endif //PIXELGUI_SCENE_H
