//
// Created by Thijs on 18/06/2023.
//

#ifndef PIXELGUI_STRINGWRITER_H
#define PIXELGUI_STRINGWRITER_H

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace PG {

class StringWriter {
private:
    std::string str;

    bool shiftCharacters = false;  // enable shifted keys (e.g. capital letters)
public:
    explicit StringWriter(std::string str = "") : str(std::move(str)) { }

    /// append a string, taking into account special characters
    void write(int key, int scancode, const std::unique_ptr<std::vector<bool>> &keysPressed);

    /// append a string, taking into account special characters
    void write(const std::string &str_, const std::unique_ptr<std::vector<bool>> &keysPressed);

    /// append a string, taking into account special characters
    void write(const char* c, const std::unique_ptr<std::vector<bool>> &keysPressed);

    /// append a string, taking into account special characters
    void write(char c, const std::unique_ptr<std::vector<bool>> &keysPressed);

    /// set the string inside StringWriter
    void setString(std::string str_);

    /// get the string inside StringWriter
    [[nodiscard]] const std::string &string() const;

};

std::ostream &operator <<(std::ostream &os, const StringWriter &stringWriter);

} // PG

#endif //PIXELGUI_STRINGWRITER_H
