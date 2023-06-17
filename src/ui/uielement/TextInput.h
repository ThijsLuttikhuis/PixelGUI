//
// Created by Thijs on 17/06/2023.
//

#ifndef PIXELGUI_TEXTINPUT_H
#define PIXELGUI_TEXTINPUT_H

#include "Button.h"

namespace PG {

class TextInput : virtual public Button {
private:
    void (* callbackFuncOnPressEnter)(const std::shared_ptr<UIElement> &) = emptyCallback;

    std::string input;
public:
    TextInput() : UIElement() {
        callbackFunc = callbackOnClickTextInput;
    }

    TextInput(std::string name, const glm::vec2 &position, const glm::vec2 &size,
              int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, keyboardKey) {

        callbackFunc = callbackOnClickTextInput;
    }

    TextInput(std::string name, const glm::vec2 &position, const glm::vec2 &size, std::shared_ptr<Sprite> sprite,
              int keyboardKey = GLFW_KEY_UNKNOWN)
          : UIElement(std::move(name), position, size, std::move(sprite), keyboardKey) {

        callbackFunc = callbackOnClickTextInput;
    }

    void onKeyboardKey(int key, int action, int scanCode,
                       const std::unique_ptr<std::vector<bool>> &keysPressed) override;

    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex);



    static void callbackOnClickTextInput(const std::shared_ptr<UIElement> &uiElement);

    void setCallbackFunction(void (* func)(const std::shared_ptr<UIElement> &)) override;


    [[nodiscard]] const std::string &getInput();
};

}

#endif //PIXELGUI_TEXTINPUT_H
