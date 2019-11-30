/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ClientGameNetworkEntitySyncSystem.cpp
*/

/* Created the 30/11/2019 at 12:48 by julian.frabel@epitech.eu */

#include <components/GameManager/GameManagerComponent.hpp>
#include "ClientGameNetworkEntitySyncSystem.hpp"

const ecs::Version rtype::ClientGameNetworkEntitySyncSystem::Version = ecs::Version("SYSTEM_ClientGameNetworkEntitySyncSystem", 0, 0, 1, 0);

const ecs::Version &rtype::ClientGameNetworkEntitySyncSystem::getType() const
{
    return Version;
}

void rtype::ClientGameNetworkEntitySyncSystem::tick(long deltatime)
{
    auto lockedWorld = _world.lock();
    if (!lockedWorld)
        return;
    auto entities = lockedWorld->getEntitiesWith({rtype::GameManagerComponent::Version});
    if (entities.empty())
        return;
    auto gameManagerEntity = entities.front().lock();
    if (!gameManagerEntity)
        return;
    auto gameManagerComp = std::dynamic_pointer_cast<rtype::GameManagerComponent>(gameManagerEntity->getComponent({rtype::GameManagerComponent::Version}).lock());
    if (!gameManagerComp)
        return;
    std::vector<int> toDestroy;
    //lockedWorld->applyToEach();
}
