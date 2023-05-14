//
// Created by Thijs Luttikhuis on 29/04/2023.
//

#ifndef PIXELGUI_PGU_H
#define PIXELGUI_PGU_H

#include <variant>
#include <list>
#include "glm/glm.hpp"
#include "messageException.h"

namespace PG {

class pgu {
public:
    typedef std::variant<char, int, double, glm::vec2, glm::vec3> anyTypeGLM;

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

    static std::string fullFile(const std::string &root, const std::string &ext);

    static std::string fullFile(const std::list<std::string>& fileParts);

    static anyTypeGLM str2vecGLM(const std::string &str);
};

}

#endif //PIXELGUI_PGU_H
