/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PlayerComponent.cpp
*/

/* Created the 28/11/2019 at 02:59 by julian.frabel@epitech.eu */

#include "PlayerComponent.hpp"

ecs::components::PlayerComponent::PlayerComponent(uint32_t score, uint8_t charge)
    : AComponent()
    , _score(score)
    , _charge(charge)
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

uint8_t ecs::components::PlayerComponent::getCharge() const
{
    return _charge;
}

void ecs::components::PlayerComponent::setCharge(uint8_t charge)
{
    _charge = charge;
}
