/*
** EPITECH PROJECT, 2022
** ShapeComponent.cpp
** File description:
** Created by tpautier,
*/

#include "CircleShapeComponent.hpp"

namespace rtype {

    const ecs::Version CircleShapeComponent::Version = ecs::Version("CircleShapeComponent", 0, 0, 0, 1);

    CircleShapeComponent::CircleShapeComponent(const sf::CircleShape&shape)
    :_shape(shape)
    {
    }

    void CircleShapeComponent::setTexture(const sf::Texture &texture)
    {
        _shape.setTexture(&texture);
    }

    void CircleShapeComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &CircleShapeComponent::getVersion() const
    {
        return CircleShapeComponent::Version;
    }

    const sf::Texture &CircleShapeComponent::getTexture() const
    {
        return (*_shape.getTexture());
    }

    void CircleShapeComponent::setColor(const sf::Color &color)
    {
        _shape.setFillColor(color);
    }

    const sf::Color &CircleShapeComponent::getColor() const
    {
        return _shape.getFillColor();
    }

    void CircleShapeComponent::setOutlineThickness(const float &outlineThickness)
    {
        _shape.setOutlineThickness(outlineThickness);
    }

    float CircleShapeComponent::getOutlineThickness() const
    {
        return _shape.getOutlineThickness();
    }

    void CircleShapeComponent::setOutlineColor(const sf::Color &color)
    {
        _shape.setOutlineColor(color);
    }

    const sf::Color &CircleShapeComponent::getOutlineColor() const
    {
        return _shape.getOutlineColor();
    }
} /* rtype */
