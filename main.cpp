//
// Created by thijs on 11-12-22.
//

#include <memory>

#include "src/window/Window.h"
#include "ui/Button.h"

int main() {

    auto window = std::make_shared<PG::Window>(512, 288);
    window->initialize();

    auto name = "Button1";
    auto pos = glm::vec2(100, 100);
    auto size = glm::vec2(16, 16);
    auto sprite = std::make_unique<PG::Sprite>("arrow");
    auto key = GLFW_KEY_A;
    auto button = std::make_shared<PG::Button>(name, pos, size, std::move(sprite), key);

    window->addUIElement(button);

    while (!window->shouldClose()) {
        window->render();
    }

    return 0;
}
