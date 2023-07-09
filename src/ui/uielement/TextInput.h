//
// Created by Thijs on 17/06/2023.
//

#ifndef PIXELGUI_TEXTINPUT_H
#define PIXELGUI_TEXTINPUT_H

#include "utilities/StringWriter.h"

#include "ButtonOnRelease.h"

namespace PG {

class TextInput : public ButtonOnRelease {
private:
    void (* callbackFuncOnPressEnter)(const std::shared_ptr<UIElement> &) = emptyCallback;

    std::unique_ptr<StringWriter> input;
public:
    TextInput() : ButtonOnRelease() {
        callbackFunc = callbackOnClickTextInput;
        input = std::make_unique<StringWriter>();
    }

    TextInput(std::string name, const glm::vec2 &position, const glm::vec2 &size,
              int keyboardKey = GLFW_KEY_UNKNOWN)
          : ButtonOnRelease(std::move(name), position, size, keyboardKey) {

        callbackFunc = callbackOnClickTextInput;
        input = std::make_unique<StringWriter>();
    }

    TextInput(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
              int keyboardKey = GLFW_KEY_UNKNOWN)
          : ButtonOnRelease(std::move(name), position, size, std::move(sprite), keyboardKey) {

        callbackFunc = callbackOnClickTextInput;
        input = std::make_unique<StringWriter>();
    }

    void onKeyboardKey(int key, int action, int scanCode,
                       const std::unique_ptr<std::vector<bool>> &keysPressed) override;

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) override;

    static void callbackOnClickTextInput(const std::shared_ptr<UIElement> &uiElement);

    void setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &)) override;

    void setInput(std::string &str);

    void setIntTextInput(const std::shared_ptr<UIElement> &uiElement);

    void setStringTextInput(const std::shared_ptr<UIElement> &uiElement);

    [[nodiscard]] const std::string &getInput();

};

}

#endif //PIXELGUI_TEXTINPUT_H
