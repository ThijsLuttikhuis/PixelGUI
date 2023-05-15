//
// Created by Thijs on 31/03/2023.
//

#include "ui/uielement/Scene.h"

#include "UIEditor.h"
#include "ui/uielement/Slider.h"
#include "ui/sprite/MultiSprite.h"

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
    std::shared_ptr<SpriteComposite> spriteComposite;
    std::shared_ptr<Sprite> sprite;
    int key;

    // 3 Side by Side Panels
    name = "LeftPanel";
    pos = glm::vec2(0, 0);
    size = glm::vec2(200, 540);
    spriteComposite = std::make_shared<SpriteComposite>(
          "rectangle; size: {200, 540}; edgeColor: {0.3, 0.5, 0.4}; fillColor: {0.3, 0.3, 0.3}; edgeWidth: 8;");

    sprite = std::make_shared<MultiSprite>(spriteComposite);

    auto leftPanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    leftPanel->setBoundObjectsInBox(true);
    leftPanel->setChangeOwnerMode(Scene::changeOwnerMode::alwaysAllowOwnerChange);

    window->addUIElement(leftPanel);

    name = "MiddlePanel";
    pos = glm::vec2(200, 0);
    size = glm::vec2(560, 540);
    spriteComposite = std::make_shared<SpriteComposite>(
          "rectangle; size: {560, 540}; edgeColor: {0.5, 0.4, 0.3}; fillColor: {0.3, 0.3, 0.3}; edgeWidth: 8;");

    sprite = std::make_shared<MultiSprite>(spriteComposite);

    auto middlePanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    middlePanel->setBoundObjectsInBox(true);
    middlePanel->setChangeOwnerMode(Scene::changeOwnerMode::alwaysAllowOwnerChange);

    window->addUIElement(middlePanel);

    name = "RightPanel";
    pos = glm::vec2(760, 0);
    size = glm::vec2(200, 540);
    spriteComposite = std::make_shared<SpriteComposite>(
          "rectangle; size: {200, 540}; edgeColor: {0.4, 0.3, 0.5}; fillColor: {0.3, 0.3, 0.3}; edgeWidth: 8;");

    sprite = std::make_shared<MultiSprite>(spriteComposite);

    auto rightPanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    rightPanel->setChangeOwnerMode(Scene::changeOwnerMode::noOwnerChange);
    rightPanel->setBoundObjectsInBox(false);

    window->addUIElement(rightPanel);

    // left panel has a button that can be copied

    name = "ButtonF";
    pos = glm::vec2(100, 100);
    size = glm::vec2(64, 64);
    sprite = std::make_shared<Sprite>("arrow");
    key = GLFW_KEY_A;

    auto buttonFactory = std::make_shared<Button>(name, pos, size,
                                                  std::move(sprite), key,
                                                  Button::pressMode::pressOnClick);
    buttonFactory->setCallbackFunction(makeDraggableButtonCopyOnClick);

    name = "ButtonM";
    pos = glm::vec2(100, 100);
    size = glm::vec2(64, 64);
    sprite = std::make_shared<Sprite>("arrow");
    key = GLFW_KEY_A;

    auto buttonM = std::make_shared<Button>(name, pos, size,
                                            std::move(sprite), key,
                                            Button::pressMode::pressOnReleaseAfterDrag);
    buttonM->setCallbackFunction(sayHi);

    name = "SliderR";
    pos = glm::vec2(50, 200);
    size = glm::vec2(80, 16);

    spriteComposite = std::make_shared<SpriteComposite>(
          "rectangle; size: {80, 16}; edgeColor: {0.3, 1.0, 0.3}; fillColor: {1.0, 0.0, 0.0};");

    sprite = std::make_shared<MultiSprite>(spriteComposite);
    key = GLFW_KEY_A;

    auto sliderR = std::make_shared<Slider>(name, pos, size,
                                            std::move(sprite), key,
                                            Slider::slideMode::horizontalOnDrag);
    sliderR->setCallbackFunction(sliderChangeColor);


    name = "SliderR2";
    pos = glm::vec2(50, 300);
    size = glm::vec2(50, 32);

    auto spriteComposite2 = std::make_shared<SpriteComposite>("rectangle; size: {20, 20};");
    sprite = std::make_shared<MultiSprite>(spriteComposite2);
    sprite->setZIndex(1.0f);

    auto sliderR2 = std::make_shared<Slider>(name, pos, size,
                                            std::move(sprite), key,
                                            Slider::slideMode::horizontalOnDrag);
    sliderR2->setCallbackFunction(sliderChangeColor);

    leftPanel->addUIElement(buttonFactory);
    middlePanel->addUIElement(buttonM);
    rightPanel->addUIElement(sliderR);
    rightPanel->addUIElement(sliderR2);

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

    draggableButtonCopy->setCallbackFunction(deleteOnReleaseIfLeftPanel);
    draggableButtonCopy->setPressMode(Button::pressMode::pressOnReleaseAfterDrag);

    if (uiElement->hasParent()) {
        auto parent = std::shared_ptr<Scene>(uiElement->getParent());

        parent->addUIElement(draggableButtonCopy);
        parent->setDraggingChildPtr(draggableButtonCopy);
    }

    draggableButtonCopy->onClick(glm::vec2(draggableButtonCopy->getPosition()));
}

void UIEditor::sayHi(const std::shared_ptr<UIElement> &uiElement) {
    DebugPrinter::print(DebugPrinter::ALL, "Hi! I'm ", uiElement->getName());
}

void UIEditor::sliderChangeColor(const std::shared_ptr<UIElement> &uiElement) {
    auto slider = std::dynamic_pointer_cast<Slider>(uiElement);

    slider->getSprite()->setBlendColor(glm::vec3((float)slider->getValue() / 100.0f));
}

void UIEditor::deleteOnReleaseIfLeftPanel(const std::shared_ptr<UIElement> &uiElement) {
    auto parentPtr = uiElement->getParent();
    if (parentPtr.expired()) {
        return;
    }
    auto parent = std::shared_ptr<Scene>(parentPtr);
    if (parent->getName() == "LeftPanel") {
        parent->removeUIElement(uiElement);
    }
}

}
