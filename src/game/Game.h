//
// Created by thijs on 13-12-22.
//

#ifndef PIXELGUI_GAME_H
#define PIXELGUI_GAME_H

#include <memory>
#include <vector>

namespace PG {

class Window;

class Game {
private:
    std::weak_ptr<Window> window;

public:
    Game() = default;

    ~Game() = default;

    virtual void render() {}

    virtual void handleMouseButton(double xPos, double yPos) {
        (void) xPos, (void) yPos;
    }

    virtual void handleMousePosition(double xPos, double yPos) {
        (void) xPos, (void) yPos;
    }

    virtual void handleKeyboard(int key, int action, const std::unique_ptr<std::vector<bool>> &keysPressed) {
        (void) key, (void) action, (void) keysPressed;
    }

    void setWindow(const std::weak_ptr<Window> &window_);
};

}

#endif //PIXELGUI_GAME_H
