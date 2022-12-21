//
// Created by thijs on 19-12-22.
//

#ifndef PIXELGUI_TESTUIELEMENT_H
#define PIXELGUI_TESTUIELEMENT_H

#include <gtest/gtest.h>
#include "game/Game.h"
#include "window/Window.h"
#include "ui/UIElement.h"

namespace testing {

using namespace PG;


class TestUIElement : public Test {

protected:

    void SetUp() override {
        xPixels = 1024;
        yPixels = 576;

        window = std::make_shared<Window>(xPixels, yPixels);
        game = std::make_shared<Game>();

        window->setGame(game);
        window->initialize();
    }

    void TearDown() override {
        window->closeWindow();
    }

public:
    int xPixels;
    int yPixels;
    std::shared_ptr<Window> window;
    std::shared_ptr<Game> game;
};

}

#endif //PIXELGUI_TESTUIELEMENT_H
