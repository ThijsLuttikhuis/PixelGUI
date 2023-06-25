//
// Created by Thijs on 22/06/2023.
//

#include "ButtonOnPress.h"

namespace PG {

void ButtonOnPress::onClick(glm::vec2 relativePos) {
    (void) relativePos;

    try {
        callbackFunc(getSharedFromThis());
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

} // PG