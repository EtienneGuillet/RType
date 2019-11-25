/*
** EPITECH PROJECT, 2022
** ShapeComponent.cpp
** File description:
** Created by tpautier,
*/

#include "RectangleShapeComponent.hpp"

namespace rtype {

    const ecs::Version AShapeComponent::Version = ecs::Version("RectangleShapeComponent", 0, 0, 0, 1);

    RectangleShapeComponent::RectangleShapeComponent(const sf::RectangleShape &shape, const int type)
    :AShapeComponent(type), _shape(shape)
    {
    }


    void RectangleShapeComponent::setTexture(const sf::Texture &texture)
    {
        _shape.setTexture(&texture);
    }

    const sf::Texture &RectangleShapeComponent::getTexture() const
    {
        return (*_shape.getTexture());
    }

    void RectangleShapeComponent::setColor(const sf::Color &color)
    {
        _shape.setFillColor(color);
    }

    const sf::Color &RectangleShapeComponent::getColor() const
    {
        return _shape.getFillColor();
    }
} /* rtype */
