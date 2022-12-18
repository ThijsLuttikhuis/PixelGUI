//
// Created by thijs on 30-05-22.
//

#ifndef DICEGONEROGUE_GAMEOBJECT_H
#define DICEGONEROGUE_GAMEOBJECT_H

#include <utility>
#include <glm/vec3.hpp>

#include "window/render/TextRenderer.h"
#include "window/render/SpriteRenderer.h"

namespace PG {

class GameObject {
private:
    static int uniqueIDCounter;
    int uniqueID;

    bool isPositionInBox(double x, double y);

    static bool isPositionInBox(double x, double y, glm::vec2 pos, glm::vec2 size);

protected:
    std::string name;

    glm::vec2 position{};
    glm::vec2 size{};

    bool mouseIsHovering = false;
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

    /// draw
    virtual void draw(const std::unique_ptr<SpriteRenderer> &spriteRenderer,
                      const std::unique_ptr<TextRenderer> &textRenderer) const;

    /// setters
    void forceSetUniqueID(int uniqueID_);

    void setPosition(glm::vec2 position_);

    void setPosition(int left, int up);

    void setSize(glm::vec2 size);

    void setIsMouseHovering(bool hover);

    /// getters
    [[nodiscard]] int getUniqueID() const;

    [[nodiscard]] const glm::vec2 &getPosition() const;

    [[nodiscard]] const glm::vec2 &getSize() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] virtual bool isMouseHovering(double xPos, double yPos) const;

    [[nodiscard]] bool isMouseHovering() const;

};

}

#endif //DICEGONEROGUE_GAMEOBJECT_H
