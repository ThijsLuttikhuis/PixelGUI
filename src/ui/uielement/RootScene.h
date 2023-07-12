//
// Created by Thijs on 14/05/2023.
//

#ifndef PIXELGUI_ROOTSCENE_H
#define PIXELGUI_ROOTSCENE_H

#include "Scene.h"
#include "window/Window.h"
#include "ui/sprite/CustomMouseSprite.h"

namespace PG {

class RootScene : public Scene {
private:
    std::weak_ptr<Window> window;
    glm::vec2 mousePosition;
    glm::vec2 mouseSize = glm::vec2(8, 12);
    std::shared_ptr<CustomMouseSprite> mouseSprite;
    std::shared_ptr<CustomMouseSprite> mouseDownSprite;
    std::weak_ptr<CustomMouseSprite> currentMouseSpritePtr = mouseSprite;

public:
    RootScene(std::string name, const std::shared_ptr<Window> &window, std::shared_ptr<CustomMouseSprite> mouseSprite, std::shared_ptr<CustomMouseSprite> mouseDownSprite)
          : Scene(std::move(name), glm::vec2(0),
                  {window->getXPixels(), window->getYPixels()}),
            window(window), mouseSprite(std::move(mouseSprite)), mouseDownSprite(std::move(mouseDownSprite)) {};

    RootScene(std::string name, const std::shared_ptr<Window> &window)
          : Scene(std::move(name), glm::vec2(0),
                  {window->getXPixels(), window->getYPixels()}), window(window) {};

    void onRelease(glm::vec2 mousePos) override;

    void onClick(glm::vec2 relativePos) override;

    void onHover(glm::vec2 mousePos) override;

    void onDrag(glm::vec2 mousePos, glm::vec2 dragStartPos) override;

    void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
              const std::unique_ptr<TextRenderer> &textRenderer, float baseZIndex) override;

    void forceSetMousePosition(glm::vec2 pos);

    void setCurrentMouseSprite(const std::shared_ptr<CustomMouseSprite> &sprite);

    void setWindow(std::weak_ptr<Window> window_);

    void setParent(std::weak_ptr<Scene> scene_) final;

    std::shared_ptr<Window> getWindow() final;

    std::shared_ptr<RootScene> getRootScene() final;

    glm::vec2 getAbsoluteMousePosition() final;

};

}

#endif //PIXELGUI_ROOTSCENE_H
