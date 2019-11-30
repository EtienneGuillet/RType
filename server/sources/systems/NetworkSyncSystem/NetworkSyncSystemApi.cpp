/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkSyncSystemApi.cpp
*/

/* Created the 28/11/2019 at 07:36 by julian.frabel@epitech.eu */

#include "NetworkSyncSystemApi.hpp"
#include "NetworkSyncSystem.hpp"

const ecs::Version systems::NetworkSyncSystemApi::Version = ecs::Version("API_NetworkSyncSystemApi", 0, 0, 1, 0);

const ecs::Version &systems::NetworkSyncSystemApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::NetworkSyncSystemApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new NetworkSyncSystem());
}
