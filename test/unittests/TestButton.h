//
// Created by thijs on 5-2-23.
//

#ifndef PIXELGUI_TESTBUTTON_H
#define PIXELGUI_TESTBUTTON_H

#include <gtest/gtest.h>
#include "game/Game.h"
#include "window/Window.h"
#include "ui/Button.h"

namespace testing {

using namespace PG;

class TestButton : public Test {

protected:

    void SetUp() override {
        button = std::make_shared<Button>("button", glm::vec2{}, glm::vec2{}, GLFW_KEY_A);
    }

    void TearDown() override {
    }

public:
    std::shared_ptr<Button> button;
};

}

#endif //PIXELGUI_TESTBUTTON_H
