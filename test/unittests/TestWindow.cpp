//
// Created by thijs on 11-12-22.
//

#include "TestWindow.h"
#include "../src/window/Window.cpp"
namespace testing {

using namespace PG;

TEST_F(TestWindow, createWindow) {

    int xp = window->getXPixels();
    int yp = window->getYPixels();
    EXPECT_EQ(xp, xPixels);
    EXPECT_EQ(yp, yPixels);
}

TEST_F(TestWindow, resizeWindow10xPixelSize) {
    int width = 160;
    int height = 90;
    window->setWindowSize(width, height);
    window->render();
    window->render();
    window->render();
    window->render();

    EXPECT_EQ(width, window->getDisplayWidth());
    EXPECT_EQ(height, window->getDisplayHeight());
}

TEST_F(TestWindow, resizeWindowTooSmallWillMakeWindowAsBigAsPixelSize) {
    int width = 50;
    int height = 45;
    window->setWindowSize(width, height);
    window->render();
    window->render();
    window->render();
    window->render();

    EXPECT_EQ(window->getXPixels(), window->getDisplayWidth());
    EXPECT_EQ(window->getYPixels(), window->getDisplayHeight());
}

TEST_F(TestWindow, resizeWindowToWrongAspectRatioWillKeepAspectRatioOfPixels) {
    int width = 500;
    int height = 500;
    window->setWindowSize(width, height);
    window->render();
    window->render();
    window->render();
    window->render();

    EXPECT_GE((double)window->getDisplayWidth() / window->getDisplayHeight(), 15.9/9);
    EXPECT_LE((double)window->getDisplayWidth() / window->getDisplayHeight(), 16.1/9);
}

}
