/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _CIRCLE_SHAPE_COMPONENT_HPP_
#define _CIRCLE_SHAPE_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class CircleShapeComponent
     * @brief This class is a component allowing to display a circle.
     */
    class CircleShapeComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param shape CircleShape displayed,
         */
        CircleShapeComponent(const sf::CircleShape &shape = sf::CircleShape(50));

        /*!
         * @brief Ctor.
         */
        ~CircleShapeComponent() = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        /*!
         * @brief Set the texture to the CircleShape.
         * @param texture Texture to set
         */
        void setTexture(const sf::Texture &texture);

        /*!
         * @brief Return the texture set to the CircleShape.
         */
        const sf::Texture &getTexture() const;

        /*!
         * @brief Set the color of the CircleShape.
         * @param color Color to set
         */
        void setColor(const sf::Color &color = sf::Color());

        /*!
         * @brief Return the Color applied to the CircleShape.
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

        const sf::CircleShape &getShape() const;

        private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::CircleShape _shape; /*!< The CircleShape displayed */
    };
} /*rtype */

#endif // _CIRCLE_SHAPE_COMPONENT_HPP_
