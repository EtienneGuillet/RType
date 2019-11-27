/*
** EPITECH PROJECT, 2022
** ShapeComponent.cpp
** File description:
** Created by tpautier,
*/

#include "ConvexShapeComponent.hpp"

namespace rtype {

    const ecs::Version ConvexShapeComponent::Version = ecs::Version("ConvexShapeComponent", 0, 0, 0, 1);

    ConvexShapeComponent::ConvexShapeComponent(const sf::ConvexShape&shape)
    :_shape(shape)
    {
    }

    void ConvexShapeComponent::setTexture(const sf::Texture &texture)
    {
        _shape.setTexture(&texture);
    }

    void ConvexShapeComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &ConvexShapeComponent::getVersion() const
    {
        return ConvexShapeComponent::Version;
    }

    const sf::Texture &ConvexShapeComponent::getTexture() const
    {
        return (*_shape.getTexture());
    }

    void ConvexShapeComponent::setColor(const sf::Color &color)
    {
        _shape.setFillColor(color);
    }

    const sf::Color &ConvexShapeComponent::getColor() const
    {
        return _shape.getFillColor();
    }

    void ConvexShapeComponent::setOutlineThickness(const float &outlineThickness)
    {
        _shape.setOutlineThickness(outlineThickness);
    }

    float ConvexShapeComponent::getOutlineThickness() const
    {
        return _shape.getOutlineThickness();
    }

    void ConvexShapeComponent::setOutlineColor(const sf::Color &color)
    {
        _shape.setOutlineColor(color);
    }

    const sf::Color &ConvexShapeComponent::getOutlineColor() const
    {
        return _shape.getOutlineColor();
    }
} /* rtype */
