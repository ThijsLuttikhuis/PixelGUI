//
// Created by Thijs Luttikhuis on 29/04/2023.
//

#include "pgu.h"

namespace PG {


    glm::vec2 &pgu::clampVec(glm::vec2 &vector, const glm::vec2 &low, const glm::vec2 &high) {
        vector.x = vector.x < low.x ? low.x : vector.x;
        vector.x = vector.x > high.x ? high.x : vector.x;
        vector.y = vector.y < low.y ? low.y : vector.y;
        vector.y = vector.y > high.y ? high.y : vector.y;
        return vector;
    }

    glm::vec3 &pgu::clampVec(glm::vec3 &vector, const glm::vec3 &low, const glm::vec3 &high) {
        vector.x = vector.x < low.x ? low.x : vector.x;
        vector.x = vector.x > high.x ? high.x : vector.x;
        vector.y = vector.y < low.y ? low.y : vector.y;
        vector.y = vector.y > high.y ? high.y : vector.y;
        vector.z = vector.z < low.z ? low.z : vector.z;
        vector.z = vector.z > high.z ? high.z : vector.z;
        return vector;
    }
};