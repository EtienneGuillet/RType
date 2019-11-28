/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PointAwarderComponent.cpp
*/

/* Created the 28/11/2019 at 06:56 by julian.frabel@epitech.eu */

#include "PointAwarderComponent.hpp"

const ecs::Version &ecs::components::PointAwarderComponent::getVersion() const
{
    return Version;
}

ecs::components::PointAwarderComponent::PointAwarderComponent(int points)
    : AComponent()
    , _points(points)
{

}

int ecs::components::PointAwarderComponent::getPoints() const
{
    return _points;
}

void ecs::components::PointAwarderComponent::setPoints(int points)
{
    _points = points;
}
