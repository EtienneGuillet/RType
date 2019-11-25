/*
** EPITECH PROJECT, 2022
** SpriteComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _SPRITE_COMPONENT_HPP_
#define _SPRITE_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
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
    class SpriteComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         */
        SpriteComponent(const int assetId);

        /*!
         * @brief Dtor.
         */
        ~SpriteComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        /*!
         * @brief Return a boolean indicating if the texture is repeated.
         */
        bool isRepeated() const;

        /*!
         * @brief Set the boolean isRepeat and change the texture reapeat state.
         * @param isRepeat boolean indicating if the texture should be repeat
         */
        void setRepeated(const bool isRepeat);

        /*!
         * @brief Return the IntRect indicating the part of the texture displayed.
         */
        const sf::IntRect &getTextureRect() const;

        /*!
         * @brief Set the IntRect indicating the part of the texture displayed.
         * @param rect IntRect indicating the part of the texture displayed.
         */
        void setTextureRect(const sf::IntRect &rect);

        /*!
         * @brief Return the Sprite displayed.
         */
        const sf::Sprite &getSprite() const;

        /*!
         * @brief Set the Sprite displayed.
         * @param sprite
         */
        void setSprite(const sf::Sprite &sprite);

        /*!
         * @brief Get the asset number.
         */
        int getAssetId() const;

        /*!
         * @brief Return a boolean indicating if the sprite is set or not.
         */
        bool isSpriteSetted() const;
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Sprite _sprite; /*!< The sprite displayed */
        bool _isRepeat; /*!< The bool indicating of the texture of the sprite should be repeat or not */
        bool _isSpriteSet; /*!< The bool indicating if the sprite is set or not */
        int _assetId; /*!< The id of the asset used to display the sprite */
    };
} /* r-type */

#endif // _SPRITE_COMPONENT_HPP_
