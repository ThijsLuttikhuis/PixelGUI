//
// Created by Thijs on 15/04/2023.
//

#ifndef PIXELGUI_UIGRID_H
#define PIXELGUI_UIGRID_H

#include "Scene.h"

namespace PG {

class UIGrid : public Scene {
private:
    int nHorizontal;
    int nVertical;

    int outerBorderSize = 0;
    int innerBorderSize = 0;

public:
    UIGrid(std::string name, const glm::vec2 &position, const glm::vec2 &size, int nHorizontal, int nVertical)
          : Scene(std::move(name), position, size), nHorizontal(nHorizontal), nVertical(nVertical) {

        children = std::vector<std::shared_ptr<UIElement>>(nHorizontal * nVertical);
    }

    UIGrid(std::string name, const glm::vec2 &position, const glm::vec2 &size,
           std::shared_ptr<Sprite> sprite, int nHorizontal, int nVertical)
          : Scene(std::move(name), position, size, std::move(sprite)),
            nHorizontal(nHorizontal), nVertical(nVertical) {

        children = std::vector<std::shared_ptr<UIElement>>(nHorizontal * nVertical);
    }

    void addUIElement(const std::shared_ptr<UIElement> &uiElement) override;

    void setUIElement(const std::shared_ptr<UIElement> &uiElement, int x, int y);

};

}

#endif //PIXELGUI_UIGRID_H
