//
// Created by thijs on 20-12-22.
//

#ifndef PIXELGUI_TESTGAMEOBJECT_H
#define PIXELGUI_TESTGAMEOBJECT_H

#include <gtest/gtest.h>
#include "../src/ui/uielement/UIElement.h"

namespace testing {

using namespace PG;

class TestGameObject : public Test {

protected:
    void SetUp() override {
        uiElement = std::make_shared<UIElement>();
    }

    void TearDown() override {
    }

public:

    std::shared_ptr<UIElement> uiElement;
};

}

#endif //PIXELGUI_TESTGAMEOBJECT_H
