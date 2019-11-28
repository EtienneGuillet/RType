/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DisplayableComponent.cpp
*/

/* Created the 28/11/2019 at 03:13 by julian.frabel@epitech.eu */

#include "DisplayableComponent.hpp"

ecs::components::DisplayableComponent::DisplayableComponent(uint32_t type)
    : AComponent()
    , _type(type)
{

}

uint32_t ecs::components::DisplayableComponent::getType() const
{
    return _type;
}

void ecs::components::DisplayableComponent::setType(uint32_t type)
{
    _type = type;
}
