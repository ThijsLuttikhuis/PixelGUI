//
// Created by Thijs on 18/06/2023.
//

#include <memory>
#include "GLFW/glfw3.h"

#include "StringWriter.h"

namespace PG {

void StringWriter::write(const std::string &str_, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    for (auto &c: str_) {
        write(&c, keysPressed);
    }
}

void StringWriter::write(char c, const std::unique_ptr<std::vector<bool>> &keysPressed) {
   write(&c, keysPressed);
}

void StringWriter::write(const char* c, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    if (keysPressed->at(GLFW_KEY_LEFT_SHIFT)) {
        str += static_cast<char>(std::toupper((int) *c));
    } else {
        str += c;
    }
}

void StringWriter::write(int key, int scancode, const std::unique_ptr<std::vector<bool>> &keysPressed) {
    const char* keyName = glfwGetKeyName(key, scancode);
    if (keyName) {
        write(keyName, keysPressed);
    }
    else if (key == GLFW_KEY_BACKSPACE) {
        if (!str.empty()) {
            str.pop_back();
        }
    }
    else if (key == GLFW_KEY_SPACE) {
        write(' ', keysPressed);
    }
}

const std::string &StringWriter::string() const {
    return str;
}

void StringWriter::setString(std::string str_) {
    str = std::move(str_);
}

std::ostream &operator <<(std::ostream &os, const StringWriter &stringWriter) {
    return os << stringWriter.string();
}

} // PG