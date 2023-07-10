//
// Created by Thijs on 02/07/2023.
//

#include "RootScene.h"
#include "CustomMouse.h"

namespace PG {

void CustomMouse::onHover(glm::vec2 mousePos) {
    (void) mousePos;

    auto rootScene = getRootScene();
    rootScene->setCurrentMouseSprite(helperSprite);
}

} // PG
