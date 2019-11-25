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

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class RectangleShapeComponent
     * @brief This class is a component allowing to display a rectangle.
     */
    class RectangleShapeComponent : protected AShapeComponent {

    public:
        /*!
         * @brief Ctor.
         * @param shape RectangleShape displayed,
         */
        RectangleShapeComponent(const sf::RectangleShape &shape, const int type);

        /*!
         * @brief Ctor.
         */
        ~RectangleShapeComponent() = default;

        /*!
         * @brief Set the texture to the RectangleShape.
         * @param texture Texture to set
         */
        void setTexture(const sf::Texture &texture);

        /*!
         * @brief Return the texture set to the RectangleShape.
         */
        const sf::Texture &getTexture() const;

        /*!
         * @brief Set the color of the RectangleShape.
         * @param color Color to set
         */
        void setColor(const sf::Color &color = sf::Color());

        /*!
         * @brief Return the Color applied to the RectangleShape.
         */
        const sf::Color &getColor() const;

    private:
        sf::RectangleShape _shape; /*!< The RectangleShape displayed */
    };
} /*rtype */

#endif // _RECTANGLE_SHAPE_COMPONENT_HPP_
