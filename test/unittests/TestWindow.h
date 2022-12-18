//
// Created by thijs on 14-12-22.
//

#ifndef PIXELGUI_TESTWINDOW_H
#define PIXELGUI_TESTWINDOW_H

#include <gtest/gtest.h>
#include "game/Game.h"
#include "../src/window/Window.h"

namespace testing {

using namespace PG;

class TestWindow : public Test {

protected:

    void SetUp() override {
        xPixels = 160;
        yPixels = 90;

        window = std::make_shared<Window>(xPixels, yPixels);
        game = std::make_shared<Game>();

        window->setGame(game);
        window->initialize();
    }

    void TearDown() override {

    }

public:
    int xPixels;
    int yPixels;
    std::shared_ptr<Window> window;
    std::shared_ptr<Game> game;
};

}

#endif //PIXELGUI_TESTWINDOW_H
