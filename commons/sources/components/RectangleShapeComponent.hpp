/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _RECTANGLE_SHAPE_COMPONENT_HPP_
#define _RECTANGLE_SHAPE_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
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
    class RectangleShapeComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param shape RectangleShape displayed,
         */
        RectangleShapeComponent(const sf::RectangleShape &shape = sf::RectangleShape(sf::Vector2f(100, 100)));

        /*!
         * @brief Ctor.
         */
        ~RectangleShapeComponent() = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

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

        /*!
         * @brief Set the thickness of the outline of the shape
         * @param outlineThickness
         */
        void setOutlineThickness(const float &outlineThickness);

        /*!
         * @brief Get the thickness of the outline of the shape
         */
        float getOutlineThickness() const;

        void setOutlineColor(const sf::Color &color);

        const sf::Color &getOutlineColor() const;

        sf::RectangleShape &getShape();
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::RectangleShape _shape; /*!< The RectangleShape displayed */
    };
} /*rtype */

#endif // _RECTANGLE_SHAPE_COMPONENT_HPP_
