//
// Created by thijs on 19-12-22.
//

#include "TestUIElement.h"

namespace testing {

using namespace PG;

TEST_F(TestUIElement, createEmptyUIElement) {
    EXPECT_EQ(uiElement->getName(), "uiElement");
    EXPECT_EQ(uiElement->getPosition(), glm::vec2{});
    EXPECT_EQ(uiElement->getSize(), glm::vec2{});
    EXPECT_FALSE(uiElement->isMouseHovering(0, 0));
}

TEST_F(TestUIElement, sizeZero_MouseHoveringAlwaysFalse) {
    ASSERT_EQ(uiElement->getPosition(), glm::vec2(0, 0));
    ASSERT_EQ(uiElement->getSize(), glm::vec2(0, 0));

    for (int x = -2; x < 3; x++) {
        for (int y = -2; y < 3; y++) {
            EXPECT_FALSE(uiElement->isMouseHovering(x, y));
        }
    }
}

TEST_F(TestUIElement, sizeNonZero_MouseHoveringExcludesBorders) {
    ASSERT_EQ(uiElement->getPosition(), glm::vec2(0, 0));
    ASSERT_EQ(uiElement->getSize(), glm::vec2(0, 0));

    int xSize = 3;
    int ySize = 4;
    int xPos = 5;
    int yPos = 6;

    uiElement->setPosition(xPos, yPos);
    uiElement->setSize(xSize, ySize);

    for (int x = xPos - 1; x < xPos + xSize + 2; x++) {
        for (int y = yPos - 1; y < yPos + ySize + 2; y++) {
            if (x >= xPos && x < xPos + xSize && y >= yPos && y < yPos + ySize) {
                EXPECT_TRUE(uiElement->isMouseHovering(x, y));
            }
            else {
                EXPECT_FALSE(uiElement->isMouseHovering(x, y));
            }
        }
    }
}

}