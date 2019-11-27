//
// Created by Lilian on 22/11/2019.
//

#include "TransformComponent.hpp"

const TransformComponent::Vector3 &TransformComponent::getPosition() const {
    return _position;
}

void TransformComponent::setPosition(const TransformComponent::Vector3 &position) {
    _position = position;
}

const TransformComponent::Vector2 &TransformComponent::getRotation() const {
    return _rotation;
}

void TransformComponent::setRotation(const TransformComponent::Vector2 &rotation) {
    _rotation = rotation;
}

const TransformComponent::Vector2 &TransformComponent::getScale() const {
    return _scale;
}

void TransformComponent::setScale(const TransformComponent::Vector2 &scale) {
    _scale = scale;
}

TransformComponent::TransformComponent(const TransformComponent::Vector3 &position, const TransformComponent::Vector2 &rotation, const TransformComponent::Vector2 &scale) :
        _position(position),
        _rotation(rotation),
        _scale(scale) {
}

TransformComponent::TransformComponent(const TransformComponent &other) :
    _position(other._position),
    _rotation(other._rotation),
    _scale(other._scale) {
}

TransformComponent &TransformComponent::operator =(const TransformComponent &rhs) {
    _position = rhs.getPosition();
    _rotation = rhs.getRotation();
    _scale = rhs.getScale();

    return *this;
}
