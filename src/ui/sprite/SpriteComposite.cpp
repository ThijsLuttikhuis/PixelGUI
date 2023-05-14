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

    int edgeWidth = 1;
    auto size = glm::vec2(0);
    auto edgeColor = glm::vec3(0.0f);
    auto fillColor = glm::vec3(1.0f);

    int entriesFound = (int)map.size();
    if (map.count("size")) {
        size = std::get<glm::vec2>(map["size"]);
        entriesFound--;
    }
    if (map.count("edgeColor")) {
        edgeColor = std::get<glm::vec3>(map["edgeColor"]);
        entriesFound--;
    }
    if (map.count("edgeWidth")) {
        edgeWidth = std::get<int>(map["edgeWidth"]);
        entriesFound--;
    }
    if (map.count("fillColor")) {
        fillColor = std::get<glm::vec3>(map["fillColor"]);
        entriesFound--;
    }

    if (entriesFound != 0) {
        DebugPrinter::print(DebugPrinter::verboseLevel::ALL, "SpriteComposite::prefabRectangle: warning: not all entries filled");
    }

    addSprite(std::make_shared<Sprite>("pixel", fillColor), {edgeWidth, edgeWidth}, size - (float)(2 * edgeWidth));
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {edgeWidth, 0}, {(int) size.x - 2 * edgeWidth, edgeWidth});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {edgeWidth, (int)size.y - edgeWidth}, {(int)size.x-2*edgeWidth, edgeWidth});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {0, 0}, {edgeWidth, size.y});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {(int)size.x - edgeWidth, 0}, {edgeWidth, size.y});
}

void SpriteComposite::draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                           const std::unique_ptr<TextRenderer> &textRenderer,
                           const std::shared_ptr<Sprite> &referenceSprite,
                           const glm::vec2 &position, const glm::vec2 &size, float baseZIndex) {

    for (unsigned long i = 0; i < sprites.size(); i++) {
        sprites[i]->setBlendColor(referenceSprite->getBlendColor());
        sprites[i]->draw(spriteRenderer, textRenderer, positions[i] + position, sizes[i], baseZIndex);
    }
}

}
