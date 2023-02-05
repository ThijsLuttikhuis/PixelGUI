//
// Created by thijs on 11-12-22.
//

#include <memory>
#include "src/window/Window.h"
#include "game/Game.h"


int main() {
    std::shared_ptr<PG::Window> window = std::make_shared<PG::Window>(512, 288);
    std::shared_ptr<PG::Game> game = std::make_shared<PG::Game>();

    window->setGame(game);
    game->setWindow(window);

    window->initialize();

    while (!window->shouldClose()) {
        window->render();
    }

    return 0;
}
