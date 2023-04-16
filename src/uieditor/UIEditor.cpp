//
// Created by Thijs on 31/03/2023.
//

#include "ui/uielement/Scene.h"

#include "UIEditor.h"

namespace PG {

std::shared_ptr<UIEditor> UIEditor::getSharedFromThis() {
    return shared_from_this();
}

UIEditor::UIEditor() {
    window = std::make_shared<Window>(960, 540, "PixelGUI Editor v1.0");
    window->initialize();
}

void UIEditor::initialize() {
    std::string name;
    glm::vec2 pos;
    glm::vec2 size;
    std::shared_ptr<Sprite> sprite;
    int key;

    // 3 Side by Side Panels

    name = "LeftPanel";
    pos = glm::vec2(0, 0);
    size = glm::vec2(200, 540);
    sprite = std::make_shared<Sprite>("square", glm::vec3(1), 0.3f);

    auto leftPanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    window->addUIElement(leftPanel);

    name = "MiddlePanel";
    pos = glm::vec2(200, 0);
    size = glm::vec2(560, 540);
    sprite = std::make_shared<Sprite>("square", glm::vec3(1), 0.3f);

    auto middlePanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    window->addUIElement(middlePanel);

    name = "RightPanel";
    pos = glm::vec2(760, 0);
    size = glm::vec2(200, 540);
    sprite = std::make_shared<Sprite>("square", glm::vec3(1), 0.3f);

    auto rightPanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    window->addUIElement(rightPanel);

    // left panel has a button that can be copied

    name = "Button1";
    pos = glm::vec2(100, 100);
    size = glm::vec2(64, 64);
    sprite = std::make_shared<Sprite>("arrow");
    key = GLFW_KEY_A;

    auto button = std::make_shared<Button>(name, pos, size, std::move(sprite), key);
    button->setCallbackFunction(makeDraggableButtonCopyOnClick);

    leftPanel->addUIElement(button);
}

void UIEditor::run() {
    while (!window->shouldClose()) {
        window->render();
    }
}

void UIEditor::makeDraggableButtonCopyOnClick(const std::shared_ptr<UIElement> &uiElement) {
    auto button = std::dynamic_pointer_cast<Button>(uiElement);

    auto draggableButtonCopy = std::make_shared<DraggableButton>(button->getName(),
                                                                 button->getPosition(), button->getSize(),
                                                                 button->getSprite());
    //TODO: draggableButtonCopy has default parameters here??
    
    auto parent = std::shared_ptr<UIElement>(uiElement->getParent());
    auto scene = std::dynamic_pointer_cast<Scene>(parent);

    scene->addUIElement(draggableButtonCopy);
    scene->setDraggingChildPtr(draggableButtonCopy);
}

}
