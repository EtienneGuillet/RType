/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ClientGameNetworkEntitySyncSystemApi.cpp
*/

/* Created the 30/11/2019 at 12:49 by julian.frabel@epitech.eu */

#include "ClientGameNetworkEntitySyncSystemApi.hpp"
#include "ClientGameNetworkEntitySyncSystem.hpp"

const ecs::Version rtype::ClientGameNetworkEntitySyncSystemApi::Version = ecs::Version("API_ClientGameNetworkEntitySyncSystemApi", 0, 0, 1, 0);

const ecs::Version &rtype::ClientGameNetworkEntitySyncSystemApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> rtype::ClientGameNetworkEntitySyncSystemApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new rtype::ClientGameNetworkEntitySyncSystem());
}
