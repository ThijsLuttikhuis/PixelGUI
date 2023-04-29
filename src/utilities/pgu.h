//
// Created by Thijs Luttikhuis on 29/04/2023.
//

#ifndef PIXELGUI_PGU_H
#define PIXELGUI_PGU_H

#include "glm/glm.hpp"

namespace PG {

class pgu {
public:

    /// clamp glm::vec2 element-wise between low and high
    static glm::vec2 &clampVec(glm::vec2 &vector, const glm::vec2 &low, const glm::vec2 &high);

    /// clamp glm::vec3 element-wise between low and high
    static glm::vec3 &clampVec(glm::vec3 &vector, const glm::vec3 &low, const glm::vec3 &high);

};

}

#endif //PIXELGUI_PGU_H
