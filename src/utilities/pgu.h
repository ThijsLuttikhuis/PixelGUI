//
// Created by Thijs Luttikhuis on 29/04/2023.
//

#ifndef PIXELGUI_PGU_H
#define PIXELGUI_PGU_H

#include <variant>
#include <list>
#include <iostream>
#include <memory>

#include "glm/glm.hpp"
#include "messageException.h"

namespace PG {

class Scene;

class pgu {
public:
    enum class positionAnchor : int {
        TopLeft, Top, TopRight,
        Left, Middle, Right,
        BottomLeft, Bottom, BottomRight
    };

    typedef std::variant<char, int, double, glm::vec2, glm::vec3, glm::vec4> anyTypeGLM;

    /**
     *
     * @param infoString std::string containing <type>; and any number of <name>: <value>; pairs.
     *                   example: "rectangle; edgeWidth: 2; size: { 10,10 }; edgeColor: {0.5, 0.5, 0};".
     * @return map of string, anytype with each string, value pair.
     */
    static std::map<std::string, anyTypeGLM> infoString2Map(const std::string &infoString);

    /// remove all characters in charsToRemove from str - example: ("chello bworclbd", "cb") returns "hello world"
    static std::string removeChars(std::string &str, const std::string &charsToRemove);

    /// converts string to anytype - example: "{1,2,3}" returns a glm::vec3 containing 1, 2 and 3.
    static anyTypeGLM str2anyTypeGLM(const std::string &str);

    /// converts string to vector (glm::vec2 or glm::vec3)
    static anyTypeGLM str2vecGLM(const std::string &str);

    /// convert integer keyboard key to string
    static std::string keyboardKey2string(int key, int scanCode);

    static glm::vec2 convertPosition(const glm::vec2 &position, pgu::positionAnchor anchor,
                                     const std::shared_ptr<Scene> &parent);
};

} // PG

#endif //PIXELGUI_PGU_H
