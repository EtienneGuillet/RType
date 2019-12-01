/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponComponent.cpp
*/

/* Created the 28/11/2019 at 02:25 by julian.frabel@epitech.eu */

#include "WeaponComponent.hpp"

const ecs::Version ecs::components::WeaponComponent::Version = ecs::Version("COMPONENT_WeaponComponent", 0, 0, 1, 0);

ecs::components::WeaponComponent::WeaponComponent(ecs::components::WeaponComponent::WeaponType type, uint32_t chargeTime)
    : AComponent()
    , _type(type)
    , _chargeTime(chargeTime)
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

uint32_t ecs::components::WeaponComponent::getChargeTime() const
{
    return _chargeTime;
}

void ecs::components::WeaponComponent::setChargeTime(uint32_t ms)
{
    _chargeTime = ms;
}

const ecs::Version &ecs::components::WeaponComponent::getVersion() const
{
    return Version;
}
