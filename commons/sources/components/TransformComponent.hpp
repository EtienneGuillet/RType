/*
** EPITECH PROJECT, 2022
** TransformComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _TRANSFORM_COMPONENT_HPP_
#define _TRANSFORM_COMPONENT_HPP_

#include "ecs/IComponent/AComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class TransformComponent
     * @brief This class is a component allowing to choose the position the scale and the rotation of an entity.
     */
    class TransformComponent : public ecs::AComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param pos Vectore3 indicating the position of the entity
         * @param rot Vectore2 indicating the rotation of the entity
         * @param scale Vectore2 indicating the scale of the entity
         */
        TransformComponent(sf::Vector3<float> pos = sf::Vector3<float>(), sf::Vector2<float> rot = sf::Vector2<float>(), sf::Vector2<float> scale = sf::Vector2<float>(1, 1));

        /*!
         * @brief Dtor.
         */
        ~TransformComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        /*!
         * @brief Return a Vector3 with the position of the entity.
         */
        const sf::Vector3<float> &getPosition() const;

        /*!
         * @brief Return a Vector2 with the rotation of the entity.
         */
        const sf::Vector2<float> &getRotation() const;

        /*!
         * @brief Return a Vector2 with the scale of the entity.
         */
        const sf::Vector2<float> &getScale() const;

        /*!
         * @brief Set the position the entity.
         * @param position Vector3 containing the position of the entity
         */
        void setPosition(float x, float y, float z);

        /*!
         * @brief Set the rotation the entity.
         * @param rotation Vector2 containing the rotation of the entity
         */
        void setRotation(float x, float y);

        /*!
         * @brief Set the scale the entity.
         * @param scale Vector2 containing the scale of the entity
         */
        void setScale(float x, float y);

        /*!
         * @brief Get the old position of the entity.
         * @return The old position of the entity.
         */
        const sf::Vector3f &getOldPos() const;

    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Vector3<float> _pos; /*!< The position of the entity */
        sf::Vector3<float> _oldPos; /*!< The old position of the entity */
        sf::Vector2<float> _rot; /*!< The rotation of the entity */
        sf::Vector2<float> _scale; /*!< The scale of the entity */
    };
} /* rtype */

#endif // _TRANSFORM_COMPONENT_HPP_
