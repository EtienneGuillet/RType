/*
** EPITECH PROJECT, 2022
** TransformComponent.cpp
** File description:
** Created by tpautier,
*/

#include "TransformComponent.hpp"

namespace rtype {

    const ecs::Version TransformComponent::Version = ecs::Version("TransformComponent", 0, 0, 0, 1);

    TransformComponent::TransformComponent(sf::Vector3<float> pos, sf::Vector2<float> rot, sf::Vector2<float> scale)
    : _pos(pos), _rot(rot), _scale(scale)
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test TransformComponent");
    }

    void TransformComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &TransformComponent::getVersion() const
    {
        return TransformComponent::Version;
    }

    sf::Vector3<float> TransformComponent::getPosition() const
    {
        return (_pos);
    }

    sf::Vector2<float> TransformComponent::getRotation() const
    {
        return (_rot);
    }

    sf::Vector2<float> TransformComponent::getScale() const
    {
        return (_scale);
    }

    void TransformComponent::setPosition(sf::Vector3<float> &position)
    {
        _pos = position;
    }

    void TransformComponent::setRotation(sf::Vector2<float> &rotation)
    {
        _rot = rotation;
    }

    void TransformComponent::setScale(sf::Vector2<float> &scale)
    {
        _scale = scale;
    }
} /* rtype */
