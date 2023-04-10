//
// Created by Thijs on 31/03/2023.
//

#include "UIEditor.h"
#include "ui/Scene.h"
#include "ui/Button.h"
#include "ui/DraggableButton.h"

namespace PG {

void testFunc();

UIEditor::UIEditor() {
    window = std::make_shared<Window>(1336, 768, "PixelGUI Editor v1.0");
    window->initialize();

    std::string name;
    glm::vec2 pos;
    glm::vec2 size;
    std::unique_ptr<PG::Sprite> sprite;
    int key;

    name = "Button1";
    pos = glm::vec2(100, 100);
    size = glm::vec2(64, 64);
    sprite = std::make_unique<PG::Sprite>("arrow");
    key = GLFW_KEY_A;
    auto button = std::make_shared<PG::DraggableButton>(name, pos, size, std::move(sprite), key);

    window->addUIElement(button);

    name = "Scene1";
    pos = glm::vec2(200, 100);
    size = glm::vec2(400, 400);
    sprite = std::make_unique<PG::Sprite>("square", glm::vec3(1), 0.3f);

    auto scene = std::make_shared<PG::Scene>(name, pos, size, std::move(sprite));

    window->addUIElement(scene);

    name = "Button2";
    pos = glm::vec2(0, 0);
    size = glm::vec2(32, 32);
    sprite = std::make_unique<PG::Sprite>("arrow");
    key = GLFW_KEY_S;
    auto button2 = std::make_shared<PG::DraggableButton>(name, pos, size, std::move(sprite), key);

    scene->addUIElement(button2);

    button2->setCallbackFunction(testFunc);
}

void UIEditor::run() {
    while (!window->shouldClose()) {
        window->render();
    }
}

void testFunc() {
    std::cout << "test" << std::endl;
}

}
