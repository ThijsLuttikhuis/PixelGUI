//
// Created by thijs on 30-05-22.
//

#include "GameObject.h"

namespace PG {

int GameObject::uniqueIDCounter = 0;

int GameObject::getUniqueID() const {
    return uniqueID;
}

const glm::vec2 &GameObject::getPosition() const {
    return position;
}

const glm::vec2 &GameObject::getSize() const {
    return size;
}

const std::string &GameObject::getName() const {
    return name;
}

void GameObject::forceSetUniqueID(int uniqueID_) {
    uniqueID = uniqueID_;
}

void GameObject::setPosition(glm::vec2 position_) {
    position = position_;
}

void GameObject::setSize(glm::vec2 size_) {
    size = size_;
}

void GameObject::setPosition(int left, int up) {
    setPosition(glm::vec2(left, up));
}

void GameObject::setSize(int width, int height) {
    setSize(glm::vec2(width, height));
}

}
