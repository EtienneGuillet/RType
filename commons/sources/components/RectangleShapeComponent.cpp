/*
** EPITECH PROJECT, 2022
** ShapeComponent.cpp
** File description:
** Created by tpautier,
*/

#include "RectangleShapeComponent.hpp"

namespace rtype {

    const ecs::Version RectangleShapeComponent::Version = ecs::Version("RectShapeComponent", 0, 0, 0, 1);

    RectangleShapeComponent::RectangleShapeComponent(const sf::RectangleShape &shape)
    :_shape(std::make_unique<sf::RectangleShape>(shape))
    {
    }

    void RectangleShapeComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &RectangleShapeComponent::getVersion() const
    {
        return RectangleShapeComponent::Version;
    }

    void RectangleShapeComponent::setTexture(const sf::Texture &texture)
    {
        _shape->setTexture(&texture);
    }

    const sf::Texture &RectangleShapeComponent::getTexture() const
    {
        return (*_shape->getTexture());
    }

    void RectangleShapeComponent::setColor(const sf::Color &color)
    {
        _shape->setFillColor(color);
    }

    const sf::Color &RectangleShapeComponent::getColor() const
    {
        return _shape->getFillColor();
    }

    void RectangleShapeComponent::setOutlineThickness(const float &outlineThickness)
    {
        _shape->setOutlineThickness(outlineThickness);
    }

    float RectangleShapeComponent::getOutlineThickness() const
    {
        return _shape->getOutlineThickness();
    }

    void RectangleShapeComponent::setOutlineColor(const sf::Color &color)
    {
        _shape->setOutlineColor(color);
    }

    const sf::Color &RectangleShapeComponent::getOutlineColor() const
    {
        return _shape->getOutlineColor();
    }

    sf::RectangleShape& RectangleShapeComponent::getShape()
    {
        return *_shape;
    }
} /* rtype */
