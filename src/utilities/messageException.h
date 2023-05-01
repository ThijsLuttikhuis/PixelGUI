//
// Created by Thijs on 01/05/2023.
//

#ifndef PIXELGUI_MESSAGEEXCEPTION_H
#define PIXELGUI_MESSAGEEXCEPTION_H


#include <exception>
#include <string>
#include <utility>

namespace PG {

class messageException : public std::exception {

private:
    std::string message;

public:
    explicit messageException(std::string message) : message(std::move(message)) {};

    [[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        const char* cmsg = message.c_str();
        return cmsg;
    }
};

}

#endif //PIXELGUI_MESSAGEEXCEPTION_H
