/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _RECTANGLE_SHAPE_COMPONENT_HPP_
#define _RECTANGLE_SHAPE_COMPONENT_HPP_

#include "components/AShapeComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

namespace rtype {

    class RectangleShapeComponent : protected AShapeComponent {

    public:
        RectangleShapeComponent(const sf::RectangleShape &shape, const int type);
        ~RectangleShapeComponent() = default;

        void setTexture(const sf::Texture &texture);
        const sf::Texture &getTexture() const;
        void setColor(const sf::Color &color = sf::Color());
        const sf::Color &getColor() const;

    private:
        sf::RectangleShape _shape;
    };
} /*rtype */

#endif // _RECTANGLE_SHAPE_COMPONENT_HPP_
