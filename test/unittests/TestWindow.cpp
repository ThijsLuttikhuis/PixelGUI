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

TEST_F(TestWindow, resizeWindow5xPixelSize) {
    for (int i = 1; i < 5; i++) {
        int width = xPixels * i;
        int height = yPixels * i;
        window->setWindowSize(width, height);
        window->render();
        window->render();
        window->render();
        window->render();

        EXPECT_EQ(width, window->getDisplayWidth());
        EXPECT_EQ(height, window->getDisplayHeight());
    }
}

TEST_F(TestWindow, resizeWindowTooSmall_WindowAsBigAsPixelSize) {
    for (int i = 1; i < 5; i++) {
        int width = xPixels / i;
        int height = yPixels / i;
        window->setWindowSize(width, height);
        window->render();
        window->render();
        window->render();
        window->render();

        EXPECT_EQ(window->getXPixels(), window->getDisplayWidth());
        EXPECT_EQ(window->getYPixels(), window->getDisplayHeight());
    }
}

TEST_F(TestWindow, resizeWindowWrongAspectRatio_WillKeepAspectRatioOfPixels) {
    int width = xPixels;
    int height = yPixels;
    double aspectRatio = (double) width / height;

    for (int i = 2; i < 6; i++) {
        for (int j = 2; j < 6; j++) {
            int width1 = xPixels * i;
            int height1 = yPixels * j;
            window->setWindowSize(width1, height1);
            window->render();
            window->render();
            window->render();
            window->render();

            EXPECT_GE((double) window->getDisplayWidth() / window->getDisplayHeight(), aspectRatio*0.95);
            EXPECT_LE((double) window->getDisplayWidth() / window->getDisplayHeight(), aspectRatio*1.05);
        }
    }
}

TEST_F(TestWindow, resizeWindowWrongA_WillKeepAspectRatioOfPixels) {
    int width = xPixels;
    int height = yPixels;
    double aspectRatio = (double) width / height;

    for (int i = 2; i < 6; i++) {
        for (int j = 2; j < 6; j++) {
            int width1 = xPixels * i;
            int height1 = yPixels * j;
            window->setWindowSize(width1, height1);
            window->render();
            window->render();
            window->render();
            window->render();

            EXPECT_GE((double) window->getDisplayWidth() / window->getDisplayHeight(), aspectRatio*0.95);
            EXPECT_LE((double) window->getDisplayWidth() / window->getDisplayHeight(), aspectRatio*1.05);
        }
    }
}

}
