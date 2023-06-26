//
// Created by Thijs on 26/06/2023.
//

#ifndef PIXELGUI_RECTANGLESPRITECOMPOSITE_H
#define PIXELGUI_RECTANGLESPRITECOMPOSITE_H

#include "SpriteComposite.h"

namespace PG {

class RectangleSpriteComposite : public SpriteComposite {
private:

public:
    explicit RectangleSpriteComposite(const std::string &prefabString = "rectangle: size: {4,4} edgeColor: {0.3, 0.3, 0.3} fillColor: {1.0, 1.0, 1.0}");

    RectangleSpriteComposite(const glm::vec2 &size, int edgeWidth, const glm::vec3 &edgeColor, const glm::vec3 &fillColor);
};

} // PG

#endif //PIXELGUI_RECTANGLESPRITECOMPOSITE_H
