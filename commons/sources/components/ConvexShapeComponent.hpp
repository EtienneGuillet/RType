/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _CONVEX_SHAPE_COMPONENT_HPP_
#define _CONVEX_SHAPE_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class ConvexShapeComponent
     * @brief This class is a component allowing to display a convex.
     */
    class ConvexShapeComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param shape ConvexShape displayed,
         */
        ConvexShapeComponent(const sf::ConvexShape &shape);

        /*!
         * @brief Ctor.
         */
        ~ConvexShapeComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        /*!
         * @brief Set the texture to the ConvexShape.
         * @param texture Texture to set
         */
        void setTexture(const sf::Texture &texture);

        /*!
         * @brief Return the texture set to the ConvexShape.
         */
        const sf::Texture &getTexture() const;

        /*!
         * @brief Set the color of the ConvexShape.
         * @param color Color to set
         */
        void setColor(const sf::Color &color = sf::Color());

        /*!
         * @brief Return the Color applied to the ConvexShape.
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

        sf::ConvexShape &getShape();
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        std::unique_ptr<sf::ConvexShape> _shape; /*!< The ConvexShape displayed */
    };
} /*rtype */

#endif // _CONVEX_SHAPE_COMPONENT_HPP_
