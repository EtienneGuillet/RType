/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** GameManagerComponent.cpp
*/

/* Created the 30/11/2019 at 06:03 by julian.frabel@epitech.eu */

#include "GameManagerComponent.hpp"

const ecs::Version rtype::GameManagerComponent::Version = ecs::Version("GameManagerComponent", 0, 0, 1, 0);

rtype::GameManagerComponent::GameManagerComponent(rtype::NetworkState &state, bool &shouldClose)
    : _state(state)
    , _shouldClose(shouldClose)
    , _displayWidth(0)
    , _displayHeight(0)
    , _tryingToConnect(false)
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

const ecs::Version &rtype::GameManagerComponent::getVersion() const
{
    return Version;
}

void rtype::GameManagerComponent::setDisplaySize(int width, int height)
{
    _displayWidth = width;
    _displayHeight = height;
}

int rtype::GameManagerComponent::getDisplayWidth() const
{
    return _displayWidth;
}

int rtype::GameManagerComponent::getDisplayHeight() const
{
    return _displayHeight;
}

void rtype::GameManagerComponent::startConnecting()
{
    _tryingToConnect = true;
}

void rtype::GameManagerComponent::stopConnecting()
{
    _tryingToConnect = false;
}

bool rtype::GameManagerComponent::isTryingToConnect() const
{
    return _tryingToConnect;
}


