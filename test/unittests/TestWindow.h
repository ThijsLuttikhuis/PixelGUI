//
// Created by thijs on 14-12-22.
//

#ifndef PIXELGUI_TESTWINDOW_H
#define PIXELGUI_TESTWINDOW_H

#include <gtest/gtest.h>
#include "../src/window/Window.h"

namespace testing {

using namespace PG;

class TestWindow : public Test {

protected:

    void SetUp() override {

        xPixels = 200;
        yPixels = 110;

        window = std::make_shared<Window>(xPixels, yPixels, "TestWindow");
        window->initialize();

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        std::cout << "Monitor resolution: " << mode->width << "x"
                  << mode->height << std::endl;
    }

    void TearDown() override {
        window->closeWindow();
    }

public:
    int xPixels;
    int yPixels;
    std::shared_ptr<Window> window;
};

}

#endif //PIXELGUI_TESTWINDOW_H
