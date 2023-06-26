//
// Created by Thijs on 26/06/2023.
//

#include "RectangleSpriteComposite.h"

namespace PG {

RectangleSpriteComposite::RectangleSpriteComposite(const std::string &prefabString) {
    auto entries = pgu::infoString2Map(prefabString);

    int edgeWidth = 1;
    auto size = glm::vec2(0);
    auto edgeColor = glm::vec3(0.0f);
    auto fillColor = glm::vec3(1.0f);

    int entriesFound = (int) entries.size();
    if (entries.count("size")) {
        size = std::get<glm::vec2>(entries["size"]);
        entriesFound--;
    }
    if (entries.count("edgeColor")) {
        edgeColor = std::get<glm::vec3>(entries["edgeColor"]);
        entriesFound--;
    }
    if (entries.count("edgeWidth")) {
        edgeWidth = std::get<int>(entries["edgeWidth"]);
        entriesFound--;
    }
    if (entries.count("fillColor")) {
        fillColor = std::get<glm::vec3>(entries["fillColor"]);
        entriesFound--;
    }

    if (entriesFound != 0) {
        DebugPrinter::print(DebugPrinter::verboseLevel::ALL,
                            "SpriteComposite::prefabRectangle: warning: not all entries filled");
    }

    std::shared_ptr<RectangleSpriteComposite> rectangleSpriteComposite = std::make_shared<RectangleSpriteComposite>(
          size, edgeWidth, edgeColor, fillColor);

    addSprite(std::make_shared<Sprite>("pixel", fillColor), {edgeWidth, edgeWidth}, size - (float) (2 * edgeWidth));
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {edgeWidth, 0}, {(int) size.x - 2 * edgeWidth, edgeWidth});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {edgeWidth, (int) size.y - edgeWidth},
              {(int) size.x - 2 * edgeWidth, edgeWidth});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {0, 0}, {edgeWidth, size.y});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {(int) size.x - edgeWidth, 0}, {edgeWidth, size.y});
}

RectangleSpriteComposite::RectangleSpriteComposite(const glm::vec2 &size, int edgeWidth, const glm::vec3 &edgeColor,
                                                   const glm::vec3 &fillColor) {

    addSprite(std::make_shared<Sprite>("pixel", fillColor), {edgeWidth, edgeWidth}, size - (float) (2 * edgeWidth));
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {edgeWidth, 0}, {(int) size.x - 2 * edgeWidth, edgeWidth});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {edgeWidth, (int) size.y - edgeWidth},
              {(int) size.x - 2 * edgeWidth, edgeWidth});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {0, 0}, {edgeWidth, size.y});
    addSprite(std::make_shared<Sprite>("pixel", edgeColor), {(int) size.x - edgeWidth, 0}, {edgeWidth, size.y});
}

} // PG