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
#include <logger/StandardLogger.hpp>
#include "components/GameManager/GameManagerComponent.hpp"
#include "components/server/networkIdentity/NetworkIdentityComponent.hpp"
#include "ClientGameNetworkEntitySyncSystem.hpp"
#include "rtype/game/RTypeEntityType.hpp"
#include "components/TransformNetworkLagCompensation.hpp"

const std::map<int, int> rtype::ClientGameNetworkEntitySyncSystem::_networkTypeToSpriteId = {
    {ET_PLAYER_1, 47},
    {ET_PLAYER_2, 48},
    {ET_PLAYER_3, 49},
    {ET_PLAYER_4, 50},
    {ET_SHOOT_TYPE_BASIC_BASE + 30, 51},
    {ET_SHOOT_TYPE_BASIC_BASE + 60, 52},
    {ET_SHOOT_TYPE_BASIC_BASE + 90, 53},
    {ET_MONSTER_TYPE_BASE, 5},
    {ET_MONSTER_TYPE_KAMIKAZE, 8}
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
    auto width = gameManagerComp->getDisplayWidth();
    auto height = gameManagerComp->getDisplayHeight();
    if (width == 0) {
        width = 1920;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelWarn, "[ClientGameNetworkEntitySyncSystem] No width set in game manager defaulting to 1920");
    }
    if (height == 0) {
        height = 1080;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelWarn, "[ClientGameNetworkEntitySyncSystem] No height set in game manager defaulting to 1080");
    }
    std::vector<int> handeled;
    std::vector<int> toDestroy;
    lockedWorld->applyToEach({EntityIdComponent::Version},
        [&width, &height, &handeled, &toDestroy, &gameManagerComp](std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto lockedEntity = entity.lock();
        auto netIdComp = std::dynamic_pointer_cast<EntityIdComponent>(components[0].lock());
        if (!netIdComp || !lockedEntity)
            return;
        try {
            auto &entityData = gameManagerComp->getState().getEntity(netIdComp->getID());
            auto scaledPos = mapPercentCoordinatesToPixelCoordianes(entityData.getPos(), width, height);
            auto trComp = std::dynamic_pointer_cast<rtype::TransformComponent>(lockedEntity->getComponent({rtype::TransformComponent::Version}).lock());
            auto trNetCompensationComp = std::dynamic_pointer_cast<rtype::TransformNetworkLagCompensation>(lockedEntity->getComponent({rtype::TransformNetworkLagCompensation::Version}).lock());
            if (!entityData.wasPosUpdated()) {
                handeled.push_back(netIdComp->getID());
                return;
            }
            if (entityData.isShouldDisplay()) {
                auto spriteComp = std::dynamic_pointer_cast<rtype::SpriteComponent>(lockedEntity->getComponent({rtype::SpriteComponent::Version}).lock());
                if (!spriteComp) {
                    lockedEntity->addComponent(std::make_shared<rtype::SpriteComponent>(getAssetIdFromNetworkType(entityData.getType())));
                }
                if (trComp) {
                    trComp->setPosition(scaledPos.x, scaledPos.y, scaledPos.z);
                    trComp->setScale(entityData.getScale().x, entityData.getScale().y);
                    trComp->setRotation(entityData.getRot().x, entityData.getRot().y);
                }
                if (trNetCompensationComp) {
                    trNetCompensationComp->setLastNetworkPos(b12software::maths::Vector3D(scaledPos.x, scaledPos.y, scaledPos.z));
                }
            } else {
                if (trComp) {
                    trComp->setScale(0, 0);
                }
            }
            entityData.setWasPosUpdated(false);
            //todo sync health
            handeled.push_back(netIdComp->getID());
        } catch (GameStateException &e) {
            toDestroy.push_back(lockedEntity->getID());
            handeled.push_back(netIdComp->getID());
        }
    });
    for (auto &entityData : gameManagerComp->getState().getEntities()) {
        if (std::find(handeled.begin(), handeled.end(), entityData.getId()) != handeled.end())
            continue;
        auto newEntity = std::make_shared<ecs::Entity>("NetworkedEntity");
        newEntity->addComponent(std::make_shared<rtype::EntityIdComponent>(entityData.getId()));
        auto scaledPos = mapPercentCoordinatesToPixelCoordianes(entityData.getPos(), width, height);
        newEntity->addComponent(std::make_shared<rtype::TransformComponent>(
            scaledPos,
            sf::Vector2f(entityData.getRot().x, entityData.getRot().y),
            sf::Vector2f(entityData.getScale().x, entityData.getScale().y)
            ));
        auto networkCompensation = std::make_shared<rtype::TransformNetworkLagCompensation>();
        networkCompensation->setLastNetworkPos(b12software::maths::Vector3D(scaledPos.x, scaledPos.y, scaledPos.z));
        newEntity->addComponent(networkCompensation);
        if (entityData.isShouldDisplay()) {
            newEntity->addComponent(std::make_shared<rtype::SpriteComponent>(getAssetIdFromNetworkType(entityData.getType())));
        }
        //todo create health
        entityData.setWasPosUpdated(false);
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

void rtype::ClientGameNetworkEntitySyncSystem::start()
{
    ASystem::start();
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelWarn));
}

sf::Vector3f rtype::ClientGameNetworkEntitySyncSystem::mapPercentCoordinatesToPixelCoordianes(
    const b12software::maths::Vector3D &coords, int width, int height)
{
    float newX = convertRange(coords.x, 0, 1000, 0, width);
    float newY = convertRange(coords.y, 0, 1000, 0, height);
    float newZ = coords.z;
    return sf::Vector3f(newX, height - newY, newZ);
}

sf::Vector2f rtype::ClientGameNetworkEntitySyncSystem::mapPercentCoordinatesToPixelCoordianes(
    const b12software::maths::Vector2D &coords, int width, int height)
{
    float newX = convertRange(coords.x, 0, 1000, 0, width);
    float newY = convertRange(coords.y, 0, 1000, 0, height);
    return sf::Vector2f(newX, height - newY);
}

b12software::maths::Vector3D
rtype::ClientGameNetworkEntitySyncSystem::mapPercentCoordinatesToPixelCoordianes(const sf::Vector3f &coords, int width,
                                                                                 int height)
{
    auto vec = mapPercentCoordinatesToPixelCoordianes(b12software::maths::Vector3D(coords.x, coords.y, coords.z), width, height);
    return b12software::maths::Vector3D(vec.x, vec.y, vec.z);
}

b12software::maths::Vector2D
rtype::ClientGameNetworkEntitySyncSystem::mapPercentCoordinatesToPixelCoordianes(const sf::Vector2f &coords, int width,
                                                                                 int height)
{
    auto vec = mapPercentCoordinatesToPixelCoordianes(b12software::maths::Vector2D(coords.x, coords.y), width, height);
    return b12software::maths::Vector2D(vec.x, vec.y);
}

float rtype::ClientGameNetworkEntitySyncSystem::convertRange(float value, float oldRangeMin, float oldRangeMax,
                                                             float newRangeMin, float newRangeMax)
{
    float oldRange = (oldRangeMax - oldRangeMin);
    if (oldRange == 0) {
        return newRangeMin;
    } else {
        float newRange = (newRangeMax - newRangeMin);
        return (((value - oldRangeMin) * newRange) / oldRange) + newRangeMin;
    }
}
