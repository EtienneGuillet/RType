/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageableComponent.cpp
*/

/* Created the 28/11/2019 at 01:45 by julian.frabel@epitech.eu */

#include "DamageableComponent.hpp"

const ecs::Version ecs::components::DamageableComponent::Version = ecs::Version("COMPONENT_DamageableComponent", 0, 0, 1, 0);

ecs::components::DamageableComponent::DamageableComponent(int hp, int maxHp)
    : AComponent()
    , _hp(hp)
    , _maxHp(maxHp)
{

}

void ecs::components::DamageableComponent::setHp(int hp)
{
    if (hp < 0)
        hp = 0;
    if (hp > _maxHp)
        hp = _maxHp;
    _hp = hp;
}

void ecs::components::DamageableComponent::setMaxHp(int maxHp)
{
    if (maxHp < 0)
        maxHp = 0;
    _maxHp = maxHp;
    if (_hp > _maxHp)
        _hp = _maxHp;
}

void ecs::components::DamageableComponent::heal(int amount)
{
    _hp += amount;
    if (_hp > _maxHp)
        _hp = _maxHp;
}

void ecs::components::DamageableComponent::damage(int amount)
{
    _hp -= amount;
    if (_hp < 0)
        _hp = 0;
}

int ecs::components::DamageableComponent::getHp() const
{
    return _hp;
}

bool ecs::components::DamageableComponent::isAlive() const
{
    return _hp != 0;
}

int ecs::components::DamageableComponent::getMaxHp() const
{
    return _maxHp;
}

const ecs::Version &ecs::components::DamageableComponent::getVersion() const
{
    return Version;
}
