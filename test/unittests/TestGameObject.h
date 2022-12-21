//
// Created by thijs on 20-12-22.
//

#ifndef PIXELGUI_TESTGAMEOBJECT_H
#define PIXELGUI_TESTGAMEOBJECT_H

#include <gtest/gtest.h>
#include "game/GameObject.h"

namespace testing {

using namespace PG;

class TestGameObject : public Test {

protected:
    void SetUp() override {
        gameObject = std::make_shared<GameObject>();
    }

    void TearDown() override {
    }

public:

    std::shared_ptr<GameObject> gameObject;
};

}

#endif //PIXELGUI_TESTGAMEOBJECT_H
