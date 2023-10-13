//
// Created by Thijs on 13/10/2023.
//

#ifndef PIXELGUI_EXTENDEDSCENE_H
#define PIXELGUI_EXTENDEDSCENE_H

#include "Scene.h"

namespace PG {

class ExtendedScene : public Scene {
public:
    ExtendedScene(std::string name, const glm::vec2 &position_, const glm::vec2 &size)
    : Scene(std::move(name), position_, size) {}

    ExtendedScene(std::string name, const glm::vec2 &position, const glm::vec2 &size,
          std::shared_ptr<Sprite> sprite)
    : Scene(std::move(name), position, size, std::move(sprite)) {}

private:


public:

};

} // PG

#endif //PIXELGUI_EXTENDEDSCENE_H
