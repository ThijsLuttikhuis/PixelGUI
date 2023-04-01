//
// Created by thijs on 06-06-22.
//

#ifndef PIXELGUI_TEXTRENDERER_H
#define PIXELGUI_TEXTRENDERER_H

#include <vector>

#include "Shader.h"
#include "Texture2D.h"

namespace PG {

class UIElement;

class TextRenderer {
private:
    static const std::vector<int> letterWidths;
    static constexpr int nLetters = 96;

    std::shared_ptr<UIElement> baseUI;

    std::shared_ptr<Shader> shader;
    unsigned int quadVAO[nLetters]{};

    std::shared_ptr<Texture2D> texture;

    glm::vec2 displayWord(const glm::vec2 &initialTextPos, const glm::vec2 &textStart,
                          const glm::vec2 &size, const std::vector<int> &wordVAO,
                          const glm::vec3 &color, float alpha, float zIndex) const;

public:
    TextRenderer(const std::shared_ptr<Shader> &shader, glm::mat4 projection);

    ~TextRenderer();

    void setBaseUI(const std::shared_ptr<UIElement> &baseUI_);

    void setTexture(const std::string &dirFolder);

    void drawText(const std::string &text, float zIndex, glm::vec2 textStart, glm::vec2 size,
                  glm::vec3 color = glm::vec3(0.0f), float alpha = 1.0f) const;

};

}

#endif //PIXELGUI_TEXTRENDERER_H
