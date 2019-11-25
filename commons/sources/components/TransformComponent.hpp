/*
** EPITECH PROJECT, 2022
** TransformComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _TRANSFORM_COMPONENT_HPP_
#define _TRANSFORM_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

namespace rtype {

    class TransformComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        TransformComponent(sf::Vector3<float> pos, sf::Vector2<float> rot, sf::Vector2<float> scale);
        ~TransformComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;
        sf::Vector3<float> getPosition() const;
        sf::Vector2<float> getRotation() const;
        sf::Vector2<float> getScale() const;
        void setPosition(sf::Vector3<float> &position);
        void setRotation(sf::Vector2<float> &rotation);
        void setScale(sf::Vector2<float> &scale);

    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Vector3<float> _pos;
        sf::Vector2<float> _rot;
        sf::Vector2<float> _scale;
    };
} /* rtype */

#endif // _TRANSFORM_COMPONENT_HPP_
