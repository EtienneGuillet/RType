/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ClientGameNetworkEntitySyncSystem.cpp
*/

/* Created the 30/11/2019 at 12:48 by julian.frabel@epitech.eu */

#include <exception/GameStateException.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <components/TransformComponent.hpp>
#include <ecs/IEntity/Entity.hpp>
#include <components/SpriteComponent.hpp>
#include <components/EntityIdComponent.hpp>
#include "components/GameManager/GameManagerComponent.hpp"
#include "components/server/networkIdentity/NetworkIdentityComponent.hpp"
#include "ClientGameNetworkEntitySyncSystem.hpp"

const std::map<int, int> rtype::ClientGameNetworkEntitySyncSystem::_networkTypeToSpriteId = {
    {1, 42}, //player 1
    {2, 42}, //player 2
    {3, 42}, //player 3
    {4, 42}, //player 4 //todo change sprites
};

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
    if (!gameManagerComp || !gameManagerComp->getState().isInGame())
        return;
    std::vector<int> handeled;
    std::vector<int> toDestroy;
    lockedWorld->applyToEach({EntityIdComponent::Version}, [&handeled, &toDestroy, &gameManagerComp](std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto lockedEntity = entity.lock();
        auto trComp = std::dynamic_pointer_cast<rtype::TransformComponent>(lockedEntity->getComponent({rtype::TransformComponent::Version}).lock());
        auto netIdComp = std::dynamic_pointer_cast<EntityIdComponent>(components[0].lock());
        if (!netIdComp || !lockedEntity)
            return;
        try {
            auto &entityData = gameManagerComp->getState().getEntity(netIdComp->getID());
            //todo change the values from percents to screen coordinates
            if (entityData.isShouldDisplay()) {
                trComp->setPosition(entityData.getPos().x, entityData.getPos().y, entityData.getPos().z);
                trComp->setScale(entityData.getScale().x, entityData.getScale().y);
                trComp->setRotation(entityData.getRot().x, entityData.getRot().y);
            } else {
                trComp->setScale(0, 0);
            }
        } catch (GameStateException &e) {
            toDestroy.push_back(lockedEntity->getID());
        }
        handeled.push_back(netIdComp->getID());
    });
    for (auto &entityData : gameManagerComp->getState().getEntities()) {
        if (std::find(handeled.begin(), handeled.end(), entityData.getId()) != handeled.end())
            continue;
        auto newEntity = std::make_shared<ecs::Entity>("NetworkedEntity");
        newEntity->addComponent(std::make_shared<rtype::EntityIdComponent>(entityData.getId()));
        //todo change the values from percents to screen coordinates
        newEntity->addComponent(std::make_shared<rtype::TransformComponent>(
            sf::Vector3f(entityData.getPos().x, entityData.getPos().y, entityData.getPos().z),
            sf::Vector2f(entityData.getRot().x, entityData.getRot().y),
            sf::Vector2f(entityData.getScale().x, entityData.getScale().y)
            ));
        newEntity->addComponent(std::make_shared<rtype::SpriteComponent>(getAssetIdFromNetworkType(entityData.getType())));
        lockedWorld->pushEntity(newEntity);
    }
    for (auto &id : toDestroy) {
        lockedWorld->popEntity(id);
    }
}

int rtype::ClientGameNetworkEntitySyncSystem::getAssetIdFromNetworkType(int type)
{
    auto it = _networkTypeToSpriteId.find(type);
    if (it != _networkTypeToSpriteId.end()) {
        return it->second;
    }
    return 0;
}
