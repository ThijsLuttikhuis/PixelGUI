//
// Created by thijs on 30-05-22.
//

#ifndef PIXELGUI_SPRITERENDERER_H
#define PIXELGUI_SPRITERENDERER_H


#include <map>
#include <vector>
#include <string>

#include "Shader.h"
#include "Texture2D.h"

namespace PG {

class Sprite;

class UIElement;

struct SpriteArgs {
    enum Anchor : int {
        TOP_LEFT = 1,
        TOP = 2,
        TOP_RIGHT = 3,
        LEFT = 4,
        MIDDLE = 5,
        RIGHT = 6,
        BOTTOM_LEFT = 7,
        BOTTOM = 8,
        BOTTOM_RIGHT = 9
    };
    enum NamedZIndex : int {

    };

    static float namedZIndexToFloat(NamedZIndex name) {
        return static_cast<float>((int) name) / 100;
    }

    explicit SpriteArgs(float zIndex, Anchor anchor = TOP_LEFT,
                        glm::mat4 model = glm::mat4(1.0))
          : zIndex(zIndex), anchor(anchor), model(model) {}

    explicit SpriteArgs(NamedZIndex namedZIndex, Anchor anchor = TOP_LEFT,
                        glm::mat4 model = glm::mat4(1.0))
          : SpriteArgs(namedZIndexToFloat(namedZIndex), anchor, model) {}

    float zIndex = 0.0f;
    Anchor anchor = BOTTOM_LEFT;
    glm::mat4 model = glm::mat4(1.0f);

};

class SpriteRenderer {
private:
    std::shared_ptr<Shader> shader;
    unsigned int quadVAO{};

    std::shared_ptr<UIElement> baseUI;
    std::map<std::string, std::shared_ptr<Texture2D>> textures;

public:
    SpriteRenderer(const std::shared_ptr<Shader> &shader, glm::mat4 projection);

    ~SpriteRenderer();

    void addTexture(const std::string &name);

    void addAllTexturesInDir(const std::string &dirName);

    void addTexture(const std::string &fileDir, const std::string &name);

    bool hasTexture(const std::string &textureName);

    void setBaseUI(std::shared_ptr<UIElement> baseUI_);

    void drawSprite(const std::unique_ptr<Sprite> &sprite, const glm::vec2 &position,
                    const glm::vec2 &size, const SpriteArgs &args) const;
};

}


#endif //PIXELGUI_SPRITERENDERER_H
