//
// Created by Lilian on 22/11/2019.
//

#include "TransformComponent.hpp"

const ecs::Version ecs::components::TransformComponent::Version = ecs::Version("COMPONENT_TransformComponent", 1, 0, 1, 0);

const ecs::components::TransformComponent::Vector3 &ecs::components::TransformComponent::getPosition() const {
    return _position;
}

void ecs::components::TransformComponent::setPosition(const TransformComponent::Vector3 &position) {
    _position = position;
}

const ecs::components::TransformComponent::Vector2 &ecs::components::TransformComponent::getRotation() const {
    return _rotation;
}

void ecs::components::TransformComponent::setRotation(const TransformComponent::Vector2 &rotation) {
    _rotation = rotation;
}

const ecs::components::TransformComponent::Vector2 &ecs::components::TransformComponent::getScale() const {
    return _scale;
}

void ecs::components::TransformComponent::setScale(const TransformComponent::Vector2 &scale) {
    _scale = scale;
}

ecs::components::TransformComponent::TransformComponent(const TransformComponent::Vector3 &position, const TransformComponent::Vector2 &rotation, const TransformComponent::Vector2 &scale) :
        _position(position),
        _rotation(rotation),
        _scale(scale) {
}

ecs::components::TransformComponent::TransformComponent(const TransformComponent &other) :
    _position(other._position),
    _rotation(other._rotation),
    _scale(other._scale) {
}

ecs::components::TransformComponent &ecs::components::TransformComponent::operator =(const TransformComponent &rhs) {
    _position = rhs.getPosition();
    _rotation = rhs.getRotation();
    _scale = rhs.getScale();

    return *this;
}

const ecs::Version &ecs::components::TransformComponent::getVersion() const
{
    return Version;
}
