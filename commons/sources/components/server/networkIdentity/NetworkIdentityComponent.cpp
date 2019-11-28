/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkIdentityComponent.cpp
*/

/* Created the 28/11/2019 at 02:14 by julian.frabel@epitech.eu */

#include "NetworkIdentityComponent.hpp"

ecs::components::NetworkIdentityComponent::NetworkIdentityComponent(uint32_t id)
    : AComponent()
    , _id(id)
{

}

void ecs::components::NetworkIdentityComponent::setNetworkId(uint32_t id)
{
    _id = id;
}

uint32_t ecs::components::NetworkIdentityComponent::getNetworkId() const
{
    return _id;
}
