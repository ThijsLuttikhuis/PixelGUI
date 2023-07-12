//
// Created by Thijs on 10/07/2023.
//

#include "PositionAnchor.h"

namespace PG {

bool AnchorTopLeft::isPositionInBox(double x, double y, glm::vec2 position, glm::vec2 size, float insideEdge) {
    bool xInBox = (x >= position.x + insideEdge && x < position.x + size.x - insideEdge);
    bool yInBox = (y >= position.y + insideEdge && y < position.y + size.y - insideEdge);
    return xInBox && yInBox;
}

bool AnchorMiddle::isPositionInBox(double x, double y, glm::vec2 position, glm::vec2 size, float insideEdge) {
    bool xInBox = (x >= position.x - size.x / 2 + insideEdge && x < position.x + size.x / 2 - insideEdge);
    bool yInBox = (y >= position.y - size.x / 2 + insideEdge && y < position.y + size.y / 2 - insideEdge);
    return xInBox && yInBox;}
} // PG