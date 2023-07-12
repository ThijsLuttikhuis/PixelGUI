//
// Created by Thijs on 17/06/2023.
//

#include "TextInput.h"
#include "Scene.h"

namespace PG {

void TextInput::setCallbackFunction(void (* func)(const std::shared_ptr<PG::UIElement> &)) {
    callbackFuncOnPressEnter = func;
}

void TextInput::callbackOnClickTextInput(const std::shared_ptr<UIElement> &uiElement) {
    if (uiElement->hasParent()) {
        std::shared_ptr<Scene> parent = uiElement->getParent();
        parent->setTextInputChild(uiElement);
    }
}

const std::string &TextInput::getInput() {
    return input->string();
}

void TextInput::onKeyboardKey(int key, int action, int scanCode,
                              const std::unique_ptr<std::vector<bool>> &keysPressed) {

    (void) action;

    std::shared_ptr<Scene> parent = getParent();
    auto textInputChild = parent->getTextInputChild();
    if (key == getKeyboardKey()) {
        if (textInputChild && textInputChild == getSharedFromThis()) {
            callbackFuncOnPressEnter(getSharedFromThis());
            parent->clearTextInputChild();
        } else {
            parent->setTextInputChild(getSharedFromThis());
        }
    }
    if (textInputChild != getSharedFromThis()) {
        return;
    }

    input->write(key, scanCode, keysPressed);
}

void TextInput::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                     const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) {

    if (!visible || !sprite) {
        return;
    }

    sprite->draw(spriteRenderer, textRenderer, position, size, baseZIndex);
    textRenderer->drawText("^" + input->string() + "^", 0.0f, position, size, glm::vec3(0.0f));
}

void TextInput::setInput(std::string &str) {
    input->setString(str);
}

void TextInput::setIntTextInput(const std::shared_ptr<UIElement> &uiElement) {
    auto textInput = std::dynamic_pointer_cast<TextInput>(uiElement);

    std::string str = textInput->getInput();
    std::string newStr;
    try {
        int strInt = std::stoi(str);
        newStr = std::to_string(strInt);
        textInput->setInput(newStr);
        callbackFuncOnPressEnter(textInput);
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

void TextInput::setStringTextInput(const std::shared_ptr<UIElement> &uiElement) {
    auto textInput = std::dynamic_pointer_cast<TextInput>(uiElement);

    callbackFuncOnPressEnter(textInput);
}

std::shared_ptr<CustomMouseSprite> &TextInput::getCustomMouse() {
    return customMouse;
}

void TextInput::setParent(std::weak_ptr<Scene> parent_) {
    UIElement::setParent(parent_);
    if (customMouse) {
        customMouse->setRootScene(getRootScene());
    }
}

void TextInput::setCustomMouse(const std::shared_ptr<CustomMouseSprite> &customMouse_) {
    customMouse = customMouse_;
    if (hasParent()) {
        customMouse->setRootScene(getRootScene());
    }
}

}
