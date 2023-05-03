//
// Created by thijs on 20-12-22.
//

#include "TestGameObject.h"

namespace testing {

using namespace PG;

TEST_F(TestGameObject, createEmptyGameObject) {
    EXPECT_TRUE(uiElement->getName().empty());
    EXPECT_EQ(uiElement->getPosition(), glm::vec2{});
    EXPECT_EQ(uiElement->getSize(), glm::vec2{});
}

TEST_F(TestGameObject, createGameObject_PosSizeAreCorrect) {
    std::string testName = "testName";
    uiElement = std::make_shared<UIElement>(testName);

    EXPECT_EQ(uiElement->getName(), testName);

    std::string testName2 = "testName2";
    glm::vec2 testPos2 = glm::vec2(2.0, 3.0);
    glm::vec2 testSize2 = glm::vec2(4.0, 5.0);

    uiElement = std::make_shared<UIElement>(testName2, testPos2, testSize2);

    EXPECT_EQ(uiElement->getName(), testName2);
    EXPECT_EQ(uiElement->getPosition(), testPos2);
    EXPECT_EQ(uiElement->getSize(), testSize2);
}

}