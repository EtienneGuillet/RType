/*
** EPITECH PROJECT, 2022
** SpriteComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _SCROLL_COMPONENT_HPP_
#define _SCROLL_COMPONENT_HPP_

#include "ecs/IComponent/AComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class SpriteComponent
     * @brief This class is a component allowing to display a sprite.
     */
    class ScrollComponent : public ecs::AComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         */
        ScrollComponent();

        /*!
         * @brief Dtor.
         */
        ~ScrollComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        void setScrollValues(const sf::Vector2<float> &_scrollValues);
        const sf::Vector2<float> &getScrollValues() const;
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Vector2<float> _scrollValues;
    };
} /* r-type */

#endif // _SCROLL_COMPONENT_HPP_
