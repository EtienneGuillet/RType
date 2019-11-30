/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ColliderComponent.cpp
*/

/* Created the 28/11/2019 at 02:42 by julian.frabel@epitech.eu */

#include "ColliderComponent.hpp"

const ecs::Version ecs::components::ColliderComponent::Version = ecs::Version("COMPONENT_ColliderComponent", 0, 0, 1, 0);

ecs::components::ColliderComponent::ColliderComponent(const b12software::maths::Vector2D &size, const b12software::maths::Vector2D &offset)
    : AComponent()
    , _size(size)
    , _offset(offset)
{

}

const b12software::maths::Vector2D &ecs::components::ColliderComponent::getSize() const
{
    return _size;
}

void ecs::components::ColliderComponent::setSize(const b12software::maths::Vector2D &size)
{
    _size = size;
}

const b12software::maths::Vector2D &ecs::components::ColliderComponent::getOffset() const
{
    return _offset;
}

void ecs::components::ColliderComponent::setOffset(const b12software::maths::Vector2D &offset)
{
    _offset = offset;
}

const ecs::Version &ecs::components::ColliderComponent::getVersion() const
{
    return Version;
}
