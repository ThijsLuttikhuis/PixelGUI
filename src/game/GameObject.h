//
// Created by thijs on 30-05-22.
//

#ifndef PIXELGUI_GAMEOBJECT_H
#define PIXELGUI_GAMEOBJECT_H

#include <utility>
#include <glm/vec3.hpp>

#include "window/render/TextRenderer.h"
#include "window/render/SpriteRenderer.h"

namespace PG {

class GameObject {
private:
    static int uniqueIDCounter;
    int uniqueID;

protected:
    std::string name;
    glm::vec2 position{};
    glm::vec2 size{};

public:
    GameObject() {
        uniqueID = uniqueIDCounter++;
    }

    explicit GameObject(std::string name) : name(std::move(name)) {
        uniqueID = uniqueIDCounter++;
    };

    GameObject(std::string name, glm::vec2 position, glm::vec2 size)
          : name(std::move(name)), position(position), size(size) {
        uniqueID = uniqueIDCounter++;
    }

    virtual ~GameObject() = default;

    bool operator ==(const GameObject &other) const {
        return uniqueID == other.uniqueID;
    }

    /// setters
    void forceSetUniqueID(int uniqueID_);

    void setPosition(glm::vec2 position_);

    void setPosition(int left, int up);

    void setSize(glm::vec2 size);

    void setSize(int width, int height);

    /// getters
    [[nodiscard]] int getUniqueID() const;

    [[nodiscard]] const glm::vec2 &getPosition() const;

    [[nodiscard]] const glm::vec2 &getSize() const;

    [[nodiscard]] const std::string &getName() const;
};

}

#endif //PIXELGUI_GAMEOBJECT_H
