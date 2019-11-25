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
         * @param texture Texture of the sprite
         */
        SpriteComponent(const sf::Texture &texture);

        /*!
         * @brief Ctor.
         * @param sprite Sprite displayed
         */
        SpriteComponent(const sf::Sprite &sprite);

        /*!
         * @brief Ctor.
         * @param fontPath String of the path to the texture file
         * @param isRepeat Bool indicating of the image of the texture file should be repeated
         * @param rect IntRect indicating the part of the texture displayed.
         */
        SpriteComponent(const std::string &fontPath, const bool isRepeat = false, const sf::IntRect &rect = sf::IntRect());

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
         * @brief Return the Texture of the sprite.
         */
        const sf::Texture &getTexture() const;

        /*!
         * @brief Set the Texture of the sprite.
         * @param texture Texture to set to the sprite
         */
        void setTexture(const sf::Texture &texture);
    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Sprite _sprite; /*!< The sprite displayed */
        bool _isRepeat; /*!< The bool indicating of the texture of the sprite should be repeat or not */
    };
} /* r-type */

#endif // _SPRITE_COMPONENT_HPP_
