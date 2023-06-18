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
    if (key == keyboardKey) {
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

}
