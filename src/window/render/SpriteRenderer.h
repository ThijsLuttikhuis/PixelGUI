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

class Scene;

class SpriteRenderer {
public:
    SpriteRenderer(const std::shared_ptr<Shader> &shader, glm::mat4 projection);

    ~SpriteRenderer();
private:
    std::shared_ptr<Shader> shader;
    unsigned int quadVAO{};

    std::shared_ptr<Scene> baseUI;
    std::map<std::string, std::shared_ptr<Texture2D>> textures;

public:


    void addTexture(const std::string &name);

    void addAllTexturesInDir(const std::string &dirName);

    void addTexture(const std::string &fileDir, const std::string &name);

    bool hasTexture(const std::string &textureName);

    void setBaseUI(const std::shared_ptr<Scene> &baseUI_);

    void drawSprite(const std::shared_ptr<Sprite> &sprite, const glm::vec2 &position, const glm::vec2 &size,
                    float baseZIndex, float rotation = 0) const;
};

}


#endif //PIXELGUI_SPRITERENDERER_H
