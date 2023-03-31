//
// Created by thijs on 5-1-23.
//

#include "Button.h"

namespace PG {

void Button::onClick(glm::vec2 relativePos) {
    UIElement::onClick(relativePos);
    try {
        callbackFunc();
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

}
