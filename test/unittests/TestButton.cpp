//
// Created by thijs on 5-2-23.
//

#include "TestButton.h"

namespace testing {

using namespace PG;

TEST_F(TestButton, createEmptyUIElement) {
    EXPECT_EQ(button->getName(), "button");
    EXPECT_EQ(button->getPosition(), glm::vec2{});
    EXPECT_EQ(button->getSize(), glm::vec2{});
    EXPECT_FALSE(button->isMouseHovering(0, 0));
}

TEST_F(TestButton, sizeZero_MouseHoveringAlwaysFalse) {
    ASSERT_EQ(button->getPosition(), glm::vec2(0, 0));
    ASSERT_EQ(button->getSize(), glm::vec2(0, 0));

    for (int x = -2; x < 3; x++) {
        for (int y = -2; y < 3; y++) {
            EXPECT_FALSE(button->isMouseHovering(x, y));
        }
    }
}

TEST_F(TestButton, sizeNonZero_MouseHoveringExcludesBorders) {
    ASSERT_EQ(button->getPosition(), glm::vec2(0, 0));
    ASSERT_EQ(button->getSize(), glm::vec2(0, 0));

    int xSize = 3;
    int ySize = 4;
    int xPos = 5;
    int yPos = 6;

    button->setPosition(xPos, yPos);
    button->setSize(xSize, ySize);

    for (int x = xPos - 1; x < xPos + xSize + 2; x++) {
        for (int y = yPos - 1; y < yPos + ySize + 2; y++) {
            if (x >= xPos && x < xPos + xSize && y >= yPos && y < yPos + ySize) {
                EXPECT_TRUE(button->isMouseHovering(x, y));
            }
            else {
                EXPECT_FALSE(button->isMouseHovering(x, y));
            }
        }
    }

}

}
