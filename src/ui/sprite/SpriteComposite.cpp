//
// Created by Thijs on 15/04/2023.
//

#include "SpriteComposite.h"

namespace PG {

SpriteComposite::SpriteComposite(const std::string &prefabString) {
    if (prefabString.starts_with("rectangle")) {
        prefabRectangle(prefabString);
    } else {
        throw messageException("SpriteComposite::SpriteComposite: prefab type not found: " + prefabString);
    }
}

void SpriteComposite::addSprite(const std::shared_ptr<Sprite> &sprite, glm::vec2 position, glm::vec2 size) {
    sprites.push_back(sprite);
    positions.push_back(position);
    sizes.push_back(size);
}

void SpriteComposite::prefabRectangle(const std::string &prefabString) {
    auto map = pgu::infoString2Map(prefabString);

    auto size = glm::vec2(0);
    auto edgeColor = glm::vec3(0.0f);
    auto fillColor = glm::vec3(1.0f);

    if (map.count("size")) {
        size = std::get<glm::vec2>(map["size"]);
    }
    if (map.count("edgeColor")) {
        edgeColor = std::get<glm::vec3>(map["edgeColor"]);
    }
    if (map.count("fillColor")) {
        fillColor = std::get<glm::vec3>(map["fillColor"]);
    }

    addSprite(std::make_shared<Sprite>("pixel", fillColor), {1, 1}, size - 2.0f);
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {1, 0}, {size.x-2, 1});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {1, size.y - 1}, {size.x-2, 1});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {0, 0}, {1, size.y});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {size.x - 1, 0}, {1, size.y});
}

void SpriteComposite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                           const std::unique_ptr<TextRenderer> &textRenderer,
                           const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<SpriteArgs> &args) {

    (void) textRenderer;

    for (unsigned long i = 0; i < sprites.size(); i++) {
        spriteRenderer->drawSprite(sprites[i], positions[i] + position, sizes[i], args);
    }
}

}
