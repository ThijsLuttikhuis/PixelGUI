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
public:
    DraggableButtonResizable() = default;

    DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                             int keyboardKey = GLFW_KEY_UNKNOWN);

    DraggableButtonResizable(std::string name, const glm::vec2 &pos, const glm::vec2 &size,
                             std::shared_ptr<Sprite> sprite, int keyboardKey = GLFW_KEY_UNKNOWN);

protected:
    struct elementEdge {
        enum class edge : int {
            top = 1,
            left = 2,
            right = 4,
            bottom = 8,
            none = 15,
            topLeft = 3,
            topRight = 5,
            bottomLeft = 10,
            bottomRight = 12
        };

        edge edge;

        explicit elementEdge(enum edge edge) : edge(edge) {};

        bool operator ==(const bool &other) const {
            return other == (bool) *this;
        }

        explicit operator bool() const {
            return (edge != edge::none);
        }

        [[nodiscard]] glm::vec2 toSlideDirection() const {
            switch (edge) {
                case edge::top:
                    return {0, -1};
                case edge::left:
                    return {-1, 0};
                case edge::right:
                    return {1, 0};
                case edge::bottom:
                    return {0, 1};
                case edge::none:
                    return {0, 0};
                case edge::topLeft:
                    return {-1, -1};
                case edge::topRight:
                    return {1, -1};
                case edge::bottomLeft:
                    return {-1, 1};
                case edge::bottomRight:
                    return {1, 1};
                default:
                    return {0, 0};
            }
        }
    };

private:
    bool resizing = false;
    bool lockSlideDir = false;

    elementEdge resizingEdge = elementEdge(elementEdge::edge::none);

    bool drawEdgeSprite = false;
    float edgeSize = 5.0f;

    std::shared_ptr<Sprite> edgeSprite{};
    std::shared_ptr<CustomMouseSprite> customMouse;

    elementEdge isPositionOnEdge(glm::vec2 mousePos);

    bool isPositionOnEdgeBool(glm::vec2 mousePos);

    static void sliderUpdateUIElementSize(const std::shared_ptr<UIElement> &uiElement);

public:

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void onClick(glm::vec2 mousePos) override;

    void onRelease(glm::vec2 mousePos) override;

    void onHover(glm::vec2 mousePos) override;

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
              const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) override;

    void setParent(std::weak_ptr<Scene> parent_) override;

    void setCustomMouse(const std::shared_ptr<CustomMouseSprite> &customMouse_);

    void setEdgeSprite(const std::shared_ptr<Sprite> &edgeSprite_);

    void setEdgeSprite(float edgeWidth = 5.0f, glm::vec4 edgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                       glm::vec4 fillColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    [[nodiscard]] std::shared_ptr<CustomMouseSprite> &getCustomMouse();

};

} // PG

#endif //PIXELGUI_DRAGGABLEBUTTONRESIZABLE_H
