//
// Created by thijs on 20-12-22.
//

#include "TestGameObject.h"

namespace testing {

using namespace PG;

TEST_F(TestGameObject, createEmptyGameObject) {
    EXPECT_TRUE(gameObject->getName().empty());
    EXPECT_EQ(gameObject->getPosition(), glm::vec2{});
    EXPECT_EQ(gameObject->getSize(), glm::vec2{});
}

TEST_F(TestGameObject, createGameObject_PosSizeAreCorrect) {
    std::string testName = "testName";
    gameObject = std::make_shared<GameObject>(testName);

    EXPECT_EQ(gameObject->getName(), testName);

    std::string testName2 = "testName2";
    glm::vec2 testPos2 = glm::vec2(2.0, 3.0);
    glm::vec2 testSize2 = glm::vec2(4.0, 5.0);

    gameObject = std::make_shared<GameObject>(testName2, testPos2, testSize2);

    EXPECT_EQ(gameObject->getName(), testName2);
    EXPECT_EQ(gameObject->getPosition(), testPos2);
    EXPECT_EQ(gameObject->getSize(), testSize2);
}

}