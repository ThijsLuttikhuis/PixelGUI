//
// Created by thijs on 30-05-22.
//

#define GLM_SWIZZLE

#include <filesystem>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "SpriteRenderer.h"
#include "ui/sprite/Sprite.h"
#include "ui/uielement/Scene.h"
#include "utilities/DebugPrinter.h"

namespace PG {

SpriteRenderer::SpriteRenderer(const std::shared_ptr<Shader> &shader, glm::mat4 projection)
      : shader(shader) {

    shader->use();
    shader->setInteger("sprite", 0);
    shader->setMatrix4("projection", projection);

    unsigned int VBO;
    float vertices[] = {
          // pos      // tex
          0.0f, 1.0f, 0.0f, 1.0f,
          1.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f,

          0.0f, 1.0f, 0.0f, 1.0f,
          1.0f, 1.0f, 1.0f, 1.0f,
          1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::addTexture(const std::string &name) {
    std::string fileName = "../src/textures/" + name + ".png";
    auto texture = std::make_shared<Texture2D>(fileName);
    textures[name] = texture;
}

void SpriteRenderer::addTexture(const std::string &fileDir, const std::string &name) {
    auto texture = std::make_shared<Texture2D>(fileDir);
    textures[name] = texture;
}

void SpriteRenderer::addAllTexturesInDir(const std::string &dirFolder) {

    auto dirIt = std::filesystem::directory_iterator(dirFolder);
    for (const auto &entry: dirIt) {

        DebugPrinter::print(DebugPrinter::ALL, "Object does not fit in scene space!");

        if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg") {

            addTexture(entry.path().string(), entry.path().stem().string());
        }
    }
}

bool SpriteRenderer::hasTexture(const std::string &textureName) {
    return textures.find(textureName) != textures.end();
}

void SpriteRenderer::setBaseUI(const std::shared_ptr<Scene> &baseUI_) {
    baseUI = baseUI_;
}

void SpriteRenderer::drawSprite(const std::shared_ptr<Sprite> &sprite, const glm::vec2 &position, const glm::vec2 &size,
                                float baseZIndex, float rotation) const {

    // move position from screen space to scene space
    glm::vec2 basePos = baseUI ? baseUI->getGlobalPosition() : glm::vec2(0, 0);
    glm::vec2 baseSize = baseUI ? baseUI->getSize() : glm::vec2(0, 0);
    glm::vec2 screenPos = position + basePos;

    // check if object fits in scene space window
    if (screenPos.x + size.x < basePos.x || screenPos.y + size.y < basePos.y ||
        position.x > baseSize.x + 1 || position.y > baseSize.y + 1) {

        DebugPrinter::print(DebugPrinter::ALL, "Object does not fit in scene space!");
        return;
    }

    auto model = glm::translate(sprite->getModel(), glm::vec3(screenPos, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // apply shader variables
    shader->use();
    shader->setMatrix4("model", model);
    shader->setVector3f("spriteColor", sprite->getColor() * sprite->getBlendColor());
    shader->setFloat("spriteAlpha", sprite->getAlpha());
    shader->setFloat("zIndex", 1.0f - 0.5f * (baseZIndex + baseZIndex * sprite->getZIndex()));

    // set texture
    glActiveTexture(GL_TEXTURE0);
    auto texture = textures.at(sprite->getTextureName());
    texture->bind();

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

}
