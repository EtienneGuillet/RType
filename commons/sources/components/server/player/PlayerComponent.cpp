/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PlayerComponent.cpp
*/

/* Created the 28/11/2019 at 02:59 by julian.frabel@epitech.eu */

#include "PlayerComponent.hpp"

const ecs::Version ecs::components::PlayerComponent::Version = ecs::Version("COMPONENT_PlayerComponent", 0, 0, 1, 0);

ecs::components::PlayerComponent::PlayerComponent(uint32_t score, uint8_t charge)
    : AComponent()
    , _score(score)
    , _charge(charge)
    , _shotPressed(false)
    , _released(false)
{

}

uint32_t ecs::components::PlayerComponent::getScore() const
{
    return _score;
}

void ecs::components::PlayerComponent::setScore(uint32_t score)
{
    _score = score;
}

float ecs::components::PlayerComponent::getCharge() const
{
    return _charge;
}

void ecs::components::PlayerComponent::setCharge(float charge)
{
    _charge = charge;
}

const ecs::Version &ecs::components::PlayerComponent::getVersion() const
{
    return Version;
}

bool ecs::components::PlayerComponent::isShotPressed() const
{
    return _shotPressed;
}

void ecs::components::PlayerComponent::setShotPressed(bool shotPressed)
{
    if (_shotPressed && !shotPressed)
        _released = true;
    else
        _released = false;
    _shotPressed = shotPressed;
}

bool ecs::components::PlayerComponent::isReleased() const
{
    return _released;
}

void ecs::components::PlayerComponent::setReleased(bool released)
{
    _released = released;
}
