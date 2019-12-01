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

    const sf::Vector3<float> &TransformComponent::getPosition() const
    {
        return (_pos);
    }

    const sf::Vector2<float> &TransformComponent::getRotation() const
    {
        return (_rot);
    }

    const sf::Vector2<float> &TransformComponent::getScale() const
    {
        return (_scale);
    }

    void TransformComponent::setPosition(float x, float y, float z)
    {
        _oldPos = _pos;
        _pos = sf::Vector3f(x, y, z);
    }

    void TransformComponent::setRotation(float x, float y)
    {
        _rot = sf::Vector2f(x, y);
    }

    void TransformComponent::setScale(float x, float y)
    {
        _scale = sf::Vector2f(x, y);
    }

    const sf::Vector3f& TransformComponent::getOldPos() const
    {
        return _oldPos;
    }
} /* rtype */
