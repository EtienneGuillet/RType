/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponComponent.cpp
*/

/* Created the 28/11/2019 at 02:25 by julian.frabel@epitech.eu */

#include "WeaponComponent.hpp"

const ecs::Version ecs::components::WeaponComponent::Version = ecs::Version("COMPONENT_WeaponComponent", 0, 0, 1, 0);

ecs::components::WeaponComponent::WeaponComponent(ecs::components::WeaponComponent::WeaponType type, uint32_t rps)
    : AComponent()
    , _type(type)
    , _rps(rps)
{

}

ecs::components::WeaponComponent::WeaponType ecs::components::WeaponComponent::getType() const
{
    return _type;
}

void ecs::components::WeaponComponent::setType(ecs::components::WeaponComponent::WeaponType type)
{
    _type = type;
}

uint32_t ecs::components::WeaponComponent::getRps() const
{
    return _rps;
}

void ecs::components::WeaponComponent::setRps(uint32_t rps)
{
    _rps = rps;
}

const ecs::Version &ecs::components::WeaponComponent::getVersion() const
{
    return Version;
}
