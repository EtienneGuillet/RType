/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RigidbodyComponent.cpp
*/

/* Created the 28/11/2019 at 02:50 by julian.frabel@epitech.eu */

#include "RigidbodyComponent.hpp"

const ecs::Version ecs::components::RigidbodyComponent::Version = ecs::Version("COMPONENT_RigidbodyComponent", 0, 0, 1, 0);

ecs::components::RigidbodyComponent::RigidbodyComponent(float ups, const b12software::maths::Vector2D &direction)
    : AComponent()
    , _direction(direction)
    , _ups(ups)
{

}

const b12software::maths::Vector2D &ecs::components::RigidbodyComponent::getDirection() const
{
    return _direction;
}

void ecs::components::RigidbodyComponent::setDirection(const b12software::maths::Vector2D &direction)
{
    _direction = direction;
}

float ecs::components::RigidbodyComponent::getUps() const
{
    return _ups;
}

void ecs::components::RigidbodyComponent::setUps(float ups)
{
    _ups = ups;
}

const ecs::Version &ecs::components::RigidbodyComponent::getVersion() const
{
    return Version;
}
