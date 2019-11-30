/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** GameManagerComponent.cpp
*/

/* Created the 30/11/2019 at 06:03 by julian.frabel@epitech.eu */

#include "GameManagerComponent.hpp"

rtype::GameManagerComponent::GameManagerComponent(rtype::NetworkState &state, bool &shouldClose)
    : _state(state)
    , _shouldClose(shouldClose)
{

}

rtype::NetworkState &rtype::GameManagerComponent::getState()
{
    return _state;
}

bool &rtype::GameManagerComponent::getShouldClose()
{
    return _shouldClose;
}
