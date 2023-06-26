//
// Created by Thijs Luttikhuis on 29/04/2023.
//

#include <algorithm>
#include <string>
#include <map>
#include <vector>

#include "GLFW/glfw3.h"

#include "pgu.h"


namespace PG {

std::string pgu::keyboardKey2string(int key, int scanCode) {
    auto knownKey = glfwGetKeyName(key, scanCode);
    if (knownKey) {
        return {knownKey};
    }

    switch (key) {
        case GLFW_KEY_ESCAPE:
            return "Escape";
        case GLFW_KEY_TAB:
            return "Tab";
        case GLFW_KEY_CAPS_LOCK:
            return "Caps";
        case GLFW_KEY_ENTER:
            return "Enter";
        case GLFW_KEY_KP_ENTER:
            return "R_Enter";
        case GLFW_KEY_LEFT_SHIFT:
            return "Shift";
        case GLFW_KEY_RIGHT_SHIFT:
            return "R_Shift";
        case GLFW_KEY_LEFT_CONTROL:
            return "Ctrl";
        case GLFW_KEY_RIGHT_CONTROL:
            return "R_Ctrl";
        case GLFW_KEY_LEFT_SUPER:
            return "Windows";
        case GLFW_KEY_RIGHT_SUPER:
            return "R_Windows";
        case GLFW_KEY_LEFT_ALT:
            return "Alt";
        case GLFW_KEY_RIGHT_ALT:
            return "R_Alt";
        case GLFW_KEY_SPACE:
            return "Space";
        case GLFW_KEY_BACKSPACE:
            return "Backspace";
        case GLFW_KEY_INSERT:
            return "Insert";
        case GLFW_KEY_DELETE:
            return "Delete";
        case GLFW_KEY_LEFT:
            return "Left";
        case GLFW_KEY_RIGHT:
            return "Right";
        case GLFW_KEY_UP:
            return "Up";
        case GLFW_KEY_DOWN:
            return "Down";
        case GLFW_KEY_MENU:
            return "Menu";
        case GLFW_KEY_END:
            return "End";
        case GLFW_KEY_HOME:
            return "Home";
        case GLFW_KEY_PAGE_UP:
            return "Pageup";
        case GLFW_KEY_PAGE_DOWN:
            return "Pagedown";
        case GLFW_KEY_PAUSE:
            return "Pause";
        case GLFW_KEY_PRINT_SCREEN:
            return "Printscreen";
        case GLFW_KEY_SCROLL_LOCK:
            return "Scrolllock";
        case GLFW_KEY_NUM_LOCK:
            return "Numlock";
        default:
            if (key > 289 && key < 315) {
                return "F" + std::to_string(key - 289);
            }
            return "Unknown";
    }
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
        return str2vecGLM(str);
    } else if (str.find(',') != std::string::npos) {
        throw messageException(
              "pgu::str2anyTypeGLM: please use curly braces to indicate a vector ('{a, b, c}'): " + str);
    } else if (str.find('.') != std::string::npos) {
        return std::stod(str);
    } else {
        return std::stoi(str);
    }
}

pgu::anyTypeGLM pgu::str2vecGLM(const std::string &str) {
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
    } else if (commas.size() == 1) {
        glm::vec2 vec;
        vec.x = std::stof(str.substr(openBracket + 1, commas[0] - openBracket));
        vec.y = std::stof(str.substr(commas[0] + 1, closeBracket - commas[0]));
        return vec;
    } else if (commas.empty()) {
        throw messageException("pgu::str2vecGLM: please use commas (,) to separate values: " + str);
    } else {
        throw messageException("pgu::str2vecGLM: vectors larger than glm::vec3 not supported: " + str);
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
