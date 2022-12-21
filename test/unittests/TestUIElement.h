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
        uiElement = std::make_shared<UIElement>("uiElement", glm::vec2{}, glm::vec2{});
    }

    void TearDown() override {
    }

public:
    std::shared_ptr<UIElement> uiElement;
};

}

#endif //PIXELGUI_TESTUIELEMENT_H
