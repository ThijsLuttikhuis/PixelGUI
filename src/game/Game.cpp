//
// Created by thijs on 13-12-22.
//

#include "Game.h"
#include "window/Window.h"

namespace PG {

void Game::setWindow(const std::weak_ptr<Window> &window_) {
    window = window_;
}

}