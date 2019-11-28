/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamagerComponent.cpp
*/

/* Created the 28/11/2019 at 03:05 by julian.frabel@epitech.eu */

#include "DamagerComponent.hpp"

const ecs::Version ecs::components::DamagerComponent::Version = ecs::Version("COMPONENT_DamagerComponent", 0, 0, 1, 0);

ecs::components::DamagerComponent::DamagerComponent(uint32_t damages, bool destroyOnHit)
    : AComponent()
    , _damages(damages)
    , _destroyOnHit(destroyOnHit)
{

}

uint32_t ecs::components::DamagerComponent::getDamages() const
{
    return _damages;
}

void ecs::components::DamagerComponent::setDamages(uint32_t damages)
{
    _damages = damages;
}

bool ecs::components::DamagerComponent::isDestroyOnHit() const
{
    return _destroyOnHit;
}

void ecs::components::DamagerComponent::setDestroyOnHit(bool destroyOnHit)
{
    _destroyOnHit = destroyOnHit;
}

const ecs::Version &ecs::components::DamagerComponent::getVersion() const
{
    return Version;
}
