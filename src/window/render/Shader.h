//
// Created by thijs on 30-05-22.
//

#ifndef PIXELGUI_SHADER_H
#define PIXELGUI_SHADER_H

#include <memory>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PG {

class Shader {
public:
    unsigned int id{};

    Shader() = default;

    // sets the current shader as active
    void use() const;

    // compiles the shader from given source code
    void compile(const std::string &vertexSource, const std::string &fragmentSource,
                 const std::string &geometrySource = "");

    void setFloat(const char* name, float value) const;

    void setInteger(const char* name, int value) const;

    void setVector2f(const char* name, float x, float y) const;

    void setVector2f(const char* name, const glm::vec2 &value) const;

    void setVector3f(const char* name, float x, float y, float z) const;

    void setVector3f(const char* name, const glm::vec3 &value) const;

    void setVector4f(const char* name, float x, float y, float z, float w) const;

    void setVector4f(const char* name, const glm::vec4 &value) const;

    void setMatrix4(const char* name, const glm::mat4 &matrix) const;

private:
    void checkCompileErrors(unsigned int object, const std::string &type) const;
};

}

#endif //PIXELGUI_SHADER_H
