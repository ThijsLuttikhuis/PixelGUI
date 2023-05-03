//
// Created by Thijs Luttikhuis on 29/04/2023.
//

#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "pgu.h"


namespace PG {


glm::vec2 &pgu::clampVec(glm::vec2 &vector, const glm::vec2 &low, const glm::vec2 &high) {
    vector.x = vector.x < low.x ? low.x : vector.x;
    vector.x = vector.x > high.x ? high.x : vector.x;
    vector.y = vector.y < low.y ? low.y : vector.y;
    vector.y = vector.y > high.y ? high.y : vector.y;
    return vector;
}

glm::vec3 &pgu::clampVec(glm::vec3 &vector, const glm::vec3 &low, const glm::vec3 &high) {
    vector.x = vector.x < low.x ? low.x : vector.x;
    vector.x = vector.x > high.x ? high.x : vector.x;
    vector.y = vector.y < low.y ? low.y : vector.y;
    vector.y = vector.y > high.y ? high.y : vector.y;
    vector.z = vector.z < low.z ? low.z : vector.z;
    vector.z = vector.z > high.z ? high.z : vector.z;
    return vector;
}

std::string pgu::removeChars(std::string &str, const std::string &charsToRemove) {
    str.erase(remove_if(str.begin(),
                        str.end(),
                        [&charsToRemove](const char &c) {
                            return charsToRemove.find(c) != std::string::npos;
                        }),
              str.end());

    return str;
}

pgu::anyTypeGLM pgu::str2anyTypeGLM(const std::string &str) {
    if (str.find('{') != std::string::npos && str.find('}') != std::string::npos) {
        auto openBracket = str.find('{');
        auto closeBracket = str.find('}');

        std::vector<unsigned long> commas;
        auto comma = str.find(',');
        while (comma != std::string::npos) {
            if (comma < openBracket || comma > closeBracket) {
                throw messageException("pgu::str2anyTypeGLM: invalid string: " + str);
            }
            commas.push_back(comma);
            comma = str.find(',', comma + 1);
        }

        if (commas.size() == 2) {
            glm::vec3 vec;
            vec.x = std::stof(str.substr(openBracket + 1, commas[0] - openBracket));
            vec.y = std::stof(str.substr(commas[0] + 1, commas[1] - commas[0]));
            vec.z = std::stof(str.substr(commas[1] + 1, closeBracket - commas[1]));
            return vec;
        }
        else if (commas.size() == 1) {
            glm::vec2 vec;
            vec.x = std::stof(str.substr(openBracket + 1, commas[0] - openBracket));
            vec.y = std::stof(str.substr(commas[0] + 1, closeBracket - commas[0]));
            return vec;
        }
        else {
            throw messageException("pgu::str2anyTypeGLM: vectors larger than glm::vec3 not supported: " + str);
        }
    }
    else {
        return std::stod(str);
    }
}

std::map<std::string, pgu::anyTypeGLM> pgu::infoString2Map(const std::string &infoString) {
    std::vector<unsigned long> colons;
    auto colon = infoString.find(':');
    while (colon != std::string::npos) {
        colons.push_back(colon);
        colon = infoString.find(':', colon + 1);
    }

    std::vector<unsigned long> semicolons;
    auto semicolon = infoString.find(';');
    while (semicolon != std::string::npos) {
        semicolons.push_back(semicolon);
        semicolon = infoString.find(';', semicolon + 1);
    }



    if (colons.size() + 1 != semicolons.size()) {
        throw messageException("pgu::infoString2Map: invalid string: " + infoString);
    }

    std::map<std::string, pgu::anyTypeGLM> strMap;
    for (unsigned long i = 0; i < colons.size(); i++) {
        std::string name = infoString.substr(semicolons[i], colons[i] - semicolons[i]);
        name = removeChars(name, " ;:");

        std::string valueStr = infoString.substr(colons[i], semicolons[i + 1] - colons[i]);
        valueStr = removeChars(valueStr, " ;:");

        auto value = str2anyTypeGLM(valueStr);

        strMap[name] = value;
    }

    return strMap;
}

}
