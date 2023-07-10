//
// Created by Thijs on 10/07/2023.
//

#ifndef PIXELGUI_POSITIONANCHOR_H
#define PIXELGUI_POSITIONANCHOR_H

#include "glm/vec2.hpp"

namespace PG {

class PositionAnchor {

private:

public:
    PositionAnchor() = default;
    virtual ~PositionAnchor() = default;

    virtual bool isPositionInBox(double x, double y, glm::vec2 pos, glm::vec2 size, float insideEdge) = 0;

};

class AnchorTopLeft : public PositionAnchor {
public:
    bool isPositionInBox(double x, double y, glm::vec2 pos, glm::vec2 size, float insideEdge) override;
};

class AnchorTop : public PositionAnchor {
public:

};

class AnchorTopRight : public PositionAnchor {

};

class AnchorLeft : public PositionAnchor {

};

class AnchorMiddle : public PositionAnchor {

};

class AnchorRight : public PositionAnchor {

};

class AnchorBottomLeft : public PositionAnchor {

};

class AnchorBottom : public PositionAnchor {

};

class AnchorBottomRight : public PositionAnchor {

};


} // PG

#endif //PIXELGUI_POSITIONANCHOR_H
