//
// Created by Thijs on 31/03/2023.
//

#include "ui/uielement/Scene.h"

#include "UIEditor.h"
#include "ui/uielement/Slider.h"
#include "ui/sprite/MultiSprite.h"
#include "ui/uielement/TextInput.h"
#include "ui/uielement/ButtonOnPress.h"
#include "ui/uielement/DraggableButtonResizable.h"

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
    spriteComposite = MultiSprite::getSpriteCompositeFromString(
          "rectangle; size: {200, 540}; edgeColor: {0.3, 0.5, 0.4}; fillColor: {0.3, 0.3, 0.3}; edgeWidth: 8;");

    sprite = std::make_shared<MultiSprite>(spriteComposite);

    auto leftPanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    leftPanel->setBoundObjectsInBox(true);
    leftPanel->setChangeOwnerMode(Scene::changeOwnerMode::alwaysAllowOwnerChange);

    window->addUIElement(leftPanel);

    name = "MiddlePanel";
    pos = glm::vec2(200, 0);
    size = glm::vec2(560, 540);
    spriteComposite = MultiSprite::getSpriteCompositeFromString(
          "rectangle; size: {560, 540}; edgeColor: {0.5, 0.4, 0.3}; fillColor: {0.3, 0.3, 0.3}; edgeWidth: 8;");

    sprite = std::make_shared<MultiSprite>(spriteComposite);

    auto middlePanel = std::make_shared<Scene>(name, pos, size, std::move(sprite));
    middlePanel->setBoundObjectsInBox(true);
    middlePanel->setChangeOwnerMode(Scene::changeOwnerMode::alwaysAllowOwnerChange);

    window->addUIElement(middlePanel);

    name = "RightPanel";
    pos = glm::vec2(760, 0);
    size = glm::vec2(200, 540);
    spriteComposite = MultiSprite::getSpriteCompositeFromString(
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

    auto buttonFactory = std::make_shared<ButtonOnPress>(name, pos, size,
                                                         std::move(sprite), key);
    buttonFactory->setCallbackFunction(makeDraggableButtonResizableCopyOnClick);

    name = "ButtonM";
    pos = glm::vec2(100, 100);
    size = glm::vec2(64, 64);
    sprite = std::make_shared<Sprite>("arrow");
    key = GLFW_KEY_A;

    auto buttonM = std::make_shared<ButtonOnRelease>(name, pos, size,
                                                     std::move(sprite), key);
    buttonM->setCallbackFunction(sayHi);

    name = "SliderR";
    pos = glm::vec2(50, 200);
    size = glm::vec2(80, 16);

    spriteComposite = MultiSprite::getSpriteCompositeFromString(
          "rectangle; size: {80, 16}; edgeColor: {0.3, 1.0, 0.3}; fillColor: {1.0, 0.0, 0.0};");

    sprite = std::make_shared<MultiSprite>(spriteComposite);
    key = GLFW_KEY_A;

    auto sliderR = std::make_shared<Slider<int>>(name, pos, size, std::move(sprite),
                                                 50, 0, 100, 50, 0.05, key);
    sliderR->setCallbackFunction(sliderChangeColor);

    name = "textInputR";
    pos = glm::vec2(50, 400);
    size = glm::vec2(80, 16);
    key = GLFW_KEY_ENTER;

    spriteComposite = MultiSprite::getSpriteCompositeFromString(
          "rectangle; size: {80, 16}; edgeColor: {0.3, 1.0, 0.3}; fillColor: {0.96, 0.96, 0.96};");

    sprite = std::make_shared<MultiSprite>(spriteComposite);


    auto textInputR = std::make_shared<TextInput>(name, pos, size,
                                                  std::move(sprite), key);
    textInputR->setCallbackFunction(setIntTextInput);


    name = "SliderR2";
    pos = glm::vec2(50, 300);
    size = glm::vec2(50, 32);

    key = GLFW_KEY_A;

    spriteComposite = MultiSprite::getSpriteCompositeFromString("rectangle; size: {20, 20};");
    sprite = std::make_shared<MultiSprite>(spriteComposite);

    auto sliderR2 = std::make_shared<Slider<int>>(name, pos, size, std::move(sprite),
                                                  50, 0, 100, 50, 0.05, key, Slider<int>::horizontalOnDrag());
    sliderR2->setCallbackFunction(sliderChangeColor);

    leftPanel->addUIElement(buttonFactory);
    middlePanel->addUIElement(buttonM);
    rightPanel->addUIElement(sliderR);
    rightPanel->addUIElement(sliderR2);
    rightPanel->addUIElement(textInputR);

}

void UIEditor::run() {
    while (!window->shouldClose()) {
        frameCounter++;
        window->render();
    }
}

void UIEditor::makeDraggableButtonResizableCopyOnClick(const std::shared_ptr<UIElement> &uiElement) {
    auto button = std::dynamic_pointer_cast<ButtonOnPress>(uiElement);

    auto draggableButtonCopy = std::make_shared<DraggableButtonResizable>(
          button->getName(), button->getPosition(),
          button->getSize(), button->getSprite());

    draggableButtonCopy->setCallbackFunction(deleteOnReleaseIfLeftPanel);

    auto parent = uiElement->getParent();
    draggableButtonCopy->Button::setParent(parent);

    parent->addUIElement(static_cast<std::shared_ptr<Button>>(draggableButtonCopy));
    parent->setDraggingChild(static_cast<std::shared_ptr<Button>>(draggableButtonCopy));

    draggableButtonCopy->onClick(glm::vec2(draggableButtonCopy->Button::getPosition()));
}

void UIEditor::sayHi(const std::shared_ptr<UIElement> &uiElement) {
    DebugPrinter::print(DebugPrinter::ALL, "Hi! I'm ", uiElement->getName());
}

void UIEditor::sliderChangeColor(const std::shared_ptr<UIElement> &uiElement) {
    auto slider = std::dynamic_pointer_cast<Slider<int>>(uiElement);
    auto value = slider->getValue();
    slider->getSprite()->setBlendColor(glm::vec3(static_cast<float>(value) / 100.0f));
}

void UIEditor::deleteOnReleaseIfLeftPanel(const std::shared_ptr<UIElement> &uiElement) {
    auto parent = uiElement->getParent();
    if (parent->getName() == "LeftPanel") {
        parent->removeUIElement(uiElement);
    }
}

void UIEditor::setIntTextInput(const std::shared_ptr<UIElement> &uiElement) {
    auto textInput = std::dynamic_pointer_cast<TextInput>(uiElement);

    std::string str = textInput->getInput();
    std::string newStr;
    try {
        int strInt = std::stoi(str);
        newStr = std::to_string(strInt);
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }

    textInput->setInput(newStr);
}

} // PG
