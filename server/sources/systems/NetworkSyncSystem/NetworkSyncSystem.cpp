/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkSyncSystem.cpp
*/

/* Created the 28/11/2019 at 07:39 by julian.frabel@epitech.eu */

#include "NetworkSyncSystem.hpp"
#include "components/server/damageable/DamageableComponent.hpp"
#include "components/server/player/PlayerComponent.hpp"
#include "components/Transform/TransformComponent.hpp"
#include "components/server/displayable/DisplayableComponent.hpp"
#include "components/server/networkIdentity/NetworkIdentityComponent.hpp"
#include "components/server/rigidbody/RigidbodyComponent.hpp"

const ecs::Version systems::NetworkSyncSystem::Version = ecs::Version("SYSTEM_NetworkSyncSystem", 0, 0, 1, 0);

systems::NetworkSyncSystem::NetworkSyncSystem()
    : ASystem()
    , _ptr()
    , _valid(false)
    , _elapsedTime(0)
    , _timeBetweenSync(150)
{

}

systems::NetworkSyncSystem::NetworkSyncSystem(const systems::NetworkSyncSystem &other)
    :  ASystem()
    , _ptr(other._ptr)
    , _valid(other._valid)
    , _elapsedTime(other._elapsedTime)
    , _timeBetweenSync(other._timeBetweenSync)
{

}

systems::NetworkSyncSystem &systems::NetworkSyncSystem::operator=(const systems::NetworkSyncSystem &rhs)
{
    if (&rhs == this)
        return *this;
    ecs::ASystem::operator=(rhs);
    _ptr = rhs._ptr;
    _valid = rhs._valid;
    _elapsedTime = rhs._elapsedTime;
    _timeBetweenSync = rhs._timeBetweenSync;
    return *this;
}

void systems::NetworkSyncSystem::tick(long deltatime)
{
    _elapsedTime += deltatime;
    if (_elapsedTime < _timeBetweenSync)
        return;
    _elapsedTime -= _timeBetweenSync;
    deltatime = _timeBetweenSync;
    auto lockedGI = _ptr.lock();
    auto lockedWorld = _world.lock();
    if (!lockedGI || !lockedWorld)
        return;
    b12software::containers::ThreadSafeList<rtype::EntityInfos> entityProcessed;
    lockedWorld->applyToEach(
        {ecs::components::NetworkIdentityComponent::Version},
        [deltatime, &entityProcessed, &lockedGI](std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            auto lockedEntity = entity.lock();
            auto lockedNetworkId = std::dynamic_pointer_cast<ecs::components::NetworkIdentityComponent>(components[0].lock());
            if (!lockedEntity || !lockedNetworkId)
                return;
            auto lockedTransform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(lockedEntity->getComponent(ecs::components::TransformComponent::Version).lock());
            auto lockedDamageable = std::dynamic_pointer_cast<ecs::components::DamageableComponent>(lockedEntity->getComponent(ecs::components::DamageableComponent::Version).lock());
            auto lockedPlayer = std::dynamic_pointer_cast<ecs::components::PlayerComponent>(lockedEntity->getComponent(ecs::components::PlayerComponent::Version).lock());
            auto lockedDisplayable = std::dynamic_pointer_cast<ecs::components::DisplayableComponent>(lockedEntity->getComponent(ecs::components::DisplayableComponent::Version).lock());
            if (lockedPlayer) {
                rtype::PlayerInfos infos;
                int idx = -1;
                for (int i = 0; i < 4; i++) {
                    auto &player = lockedGI->getPlayer(i);
                    if (player.getId() == lockedNetworkId->getNetworkId()) {
                        idx = i;
                        infos = player;
                    }
                }
                if (idx == -1)
                    return;
                auto lockedRb = std::dynamic_pointer_cast<ecs::components::RigidbodyComponent>(lockedEntity->getComponent(ecs::components::RigidbodyComponent::Version).lock());
                if (lockedRb) {
                    auto dir = b12software::maths::Vector2D(infos.isMovingRight() - infos.isMovingLeft(), infos.isMovingUp() - infos.isMovingDown());
                    if (dir.magnitude() != 0)
                        dir.normalize();
                    lockedRb->setDirection(dir);
                }
                lockedPlayer->setShotPressed(infos.isShooting());
                infos.setCharge(lockedPlayer->getCharge());
                infos.setScore(lockedPlayer->getScore());
                if (lockedDisplayable) {
                    infos.setType(lockedDisplayable->getType());
                } else {
                    infos.setType(rtype::ET_UNKNOWN);
                }
                if (lockedTransform) {
                    infos.setPosition(lockedTransform->getPosition());
                    infos.setRotation(lockedTransform->getRotation());
                    infos.setScale(lockedTransform->getScale());
                }
                if (lockedDamageable) {
                    infos.setHp(lockedDamageable->getHp());
                } else {
                    infos.setHp(0);
                }
                lockedGI->setPlayer(idx, infos);
            } else {
                rtype::EntityInfos infos;
                infos.setId(lockedNetworkId->getNetworkId());
                if (lockedDisplayable) {
                    infos.setType(lockedDisplayable->getType());
                } else {
                    infos.setType(rtype::ET_UNKNOWN);
                }
                if (lockedTransform) {
                    infos.setPosition(lockedTransform->getPosition());
                    infos.setRotation(lockedTransform->getRotation());
                    infos.setScale(lockedTransform->getScale());
                }
                if (lockedDamageable) {
                    infos.setHp(lockedDamageable->getHp());
                } else {
                    infos.setHp(0);
                }
                entityProcessed.push_back(infos);
            }
        }
    );
    lockedGI->setEntities(entityProcessed);
}

const ecs::Version &systems::NetworkSyncSystem::getType() const
{
    return Version;
}

void systems::NetworkSyncSystem::setGameInfosPtr(std::weak_ptr<rtype::GameInfos> ptr)
{
    _ptr = ptr;
    if ( _ptr.lock()) {
        _valid = true;
    } else {
        _valid = false;
    }
}

bool systems::NetworkSyncSystem::areGameInfosSet() const
{
    return _valid;
}
