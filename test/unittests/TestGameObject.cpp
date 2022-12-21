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
    EXPECT_FALSE(gameObject->isMouseHovering());
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

TEST_F(TestGameObject, sizeZero_MouseHoveringAlwaysFalse) {
    ASSERT_EQ(gameObject->getPosition(), glm::vec2(0, 0));
    ASSERT_EQ(gameObject->getSize(), glm::vec2(0, 0));

    for (int x = -2; x < 3; x++) {
        for (int y = -2; y < 3; y++) {
            EXPECT_FALSE(gameObject->isMouseHovering(x, y));
        }
    }
}

TEST_F(TestGameObject, sizeNonZero_MouseHoveringExcludesBorders) {
    ASSERT_EQ(gameObject->getPosition(), glm::vec2(0, 0));
    ASSERT_EQ(gameObject->getSize(), glm::vec2(0, 0));


    int xSize = 3;
    int ySize = 4;
    int xPos = 5;
    int yPos = 6;

    gameObject->setPosition(xPos, yPos);
    gameObject->setSize(xSize, ySize);

    for (int x = xPos - 1; x < xPos + xSize + 2; x++) {
        for (int y = yPos - 1; y < yPos + ySize + 2; y++) {
            if (x > xPos && x < xPos + xSize && y > yPos && y < yPos + ySize) {
                EXPECT_TRUE(gameObject->isMouseHovering(x, y));
            }
            else {
                EXPECT_FALSE(gameObject->isMouseHovering(x, y));
            }
        }
    }

}

}