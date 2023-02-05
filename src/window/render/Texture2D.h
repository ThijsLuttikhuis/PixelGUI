//
// Created by thijs on 30-05-22.
//

#ifndef PIXELGUI_TEXTURE2D_H
#define PIXELGUI_TEXTURE2D_H

#include <string>

#include "Shader.h"

namespace PG {

class Texture2D {
private:
    unsigned int id{};

    int width{};
    int height{};
    int channels{};

    unsigned int internalFormat;
    unsigned int imageFormat;
    unsigned int wrapS{};
    unsigned int wrapT{};
    unsigned int filterMin{};
    unsigned int filterMag{};
public:
    explicit Texture2D(const std::string &fileName);

    void bind() const;
};

}

#endif //PIXELGUI_TEXTURE2D_H
