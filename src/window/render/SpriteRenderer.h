//
// Created by thijs on 30-05-22.
//

#ifndef DICEGONEROGUE_SPRITERENDERER_H
#define DICEGONEROGUE_SPRITERENDERER_H


#include <map>
#include <vector>
#include <string>

#include "Shader.h"
#include "Texture2D.h"

namespace PG {

class UIElement;

struct SpriteArgs {
    enum Anchor {
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
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 color = glm::vec3(1.0f);
    float alpha = 1.0f;
    float zIndex = 0.0f;
    float rotation = 0.0f;
    Anchor anchor = BOTTOM_LEFT;
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

    void drawSprite(const std::string &textureName, float zIndex, const glm::vec2 &position,
                    const glm::vec2 &size, const SpriteArgs &args) const;
};

}


#endif //DICEGONEROGUE_SPRITERENDERER_H
