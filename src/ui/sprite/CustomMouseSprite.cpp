//
// Created by Thijs on 02/07/2023.
//

#include "ui/uielement/RootScene.h"
#include "CustomMouseSprite.h"

#include <utility>

namespace PG {

void CustomMouseSprite::setMouse() {
    rootScene->setCurrentMouseSprite(std::dynamic_pointer_cast<CustomMouseSprite>(getSharedFromThis()));
}

void CustomMouseSprite::setRootScene(std::shared_ptr<RootScene> rootScene_) {
    rootScene = std::move(rootScene_);
}

} // PG
