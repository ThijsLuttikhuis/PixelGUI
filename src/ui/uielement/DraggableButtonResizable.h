//
// Created by Thijs on 21/06/2023.
//

#ifndef PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H
#define PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H


#include <utility>


#include "glm/vec2.hpp"
#include "ui/uielement/DraggableButton.h"
#include "ui/uielement/Slider.h"
#include "HelperSprite.h"
#include "Slider.h"
#include "ui/sprite/CustomMouseSprite.h"
#include "ui/sprite/MultiSprite.h"
#include "ui/sprite/RectangleSpriteComposite.h"

namespace PG {

class DraggableButtonResizable : public DraggableButton, public Slider<int> {
private:
    bool resizing = false;
    bool drawEdgeSprite = false;
    int edgeSize = 5;
    glm::vec2 mouseOnEdgePosition{};

    std::shared_ptr<Sprite> edgeSprite{};
    std::shared_ptr<CustomMouseSprite> customMouse;

    bool isPositionOnEdge(glm::vec2 mousePos);

public:
    DraggableButtonResizable() = default;

    DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                             int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), pos, size, keyboardKey) {}

    DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                             std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), pos, size, std::move(sprite), keyboardKey) {}

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onClick(glm::vec2 mousePos) override;

    void onRelease(glm::vec2 mousePos) override;

    void onHover(glm::vec2 mousePos) override;

    void setParent(std::weak_ptr<Scene> parent_) override;

    void setCustomMouse(const std::shared_ptr<CustomMouseSprite> &customMouse_);

    void setEdgeSprite(const std::shared_ptr<Sprite> &edgeSprite_);

    void setEdgeSprite(int edgeWidth = 5.0f, glm::vec4 edgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                                                     glm::vec4 fillColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    [[nodiscard]] std::shared_ptr<CustomMouseSprite> &getCustomMouse();

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) override;
};

} // PG

#endif //PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H
