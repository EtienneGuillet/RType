/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageSystem.cpp
*/

/* Created the 28/11/2019 at 04:28 by julian.frabel@epitech.eu */

#include <cmath>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include "DamageSystem.hpp"
#include "components/Transform/TransformComponent.hpp"
#include "components/server/damageable/DamageableComponent.hpp"
#include "components/server/damager/DamagerComponent.hpp"
#include "components/server/collider/ColliderComponent.hpp"

const ecs::Version systems::DamageSystem::Version = ecs::Version("SYSTEM_DamageSystem", 0, 0, 1, 0);


systems::DamageSystem::DamageSystem()
    : ASystem(), _elapsedTime(0), _computeEvery(200)
{
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
}

void systems::DamageSystem::tick(long deltatime)
{
    _elapsedTime += deltatime;
    if (_elapsedTime >= _computeEvery) {
        computeDamages();
        _elapsedTime -= _computeEvery;
    }
}

const ecs::Version &systems::DamageSystem::getType() const
{
    return Version;
}

bool systems::DamageSystem::collide(const b12software::maths::Vector2D &colAPos,
                                    const b12software::maths::Vector2D &colASize,
                                    const b12software::maths::Vector2D &colBPos,
                                    const b12software::maths::Vector2D &colBSize)
{
    auto aMin = colAPos - (colASize * 0.5f);
    auto aMax = colAPos + (colASize * 0.5f);
    auto bMin = colBPos - (colBSize * 0.5f);
    auto bMax = colBPos + (colBSize * 0.5f);
    if (aMin.x < bMax.x && aMax.x > bMin.x && aMin.y > bMax.y && aMax.y > bMin.y) {
        return true;
    }
    return false;
}

void systems::DamageSystem::computeDamages() const
{
    auto lockedWorld = _world.lock();
    if (lockedWorld) {
        auto damageableEntities = lockedWorld->getEntitiesWith({ecs::components::DamageableComponent::Version, ecs::components::ColliderComponent::Version});
        auto damagerEntities = lockedWorld->getEntitiesWith({ecs::components::DamagerComponent::Version, ecs::components::ColliderComponent::Version});

        auto elapsedTime = _elapsedTime;

        damageableEntities.erase(std::remove_if(damageableEntities.begin(), damageableEntities.end(), [elapsedTime](const std::weak_ptr<ecs::IEntity> &entity) {
            auto lockedEntity = entity.lock();
            if (!lockedEntity)
                return true;
            auto damageableComponent = std::dynamic_pointer_cast<ecs::components::DamageableComponent>(lockedEntity->getComponent(ecs::components::DamageableComponent::Version).lock());
            if (!damageableComponent)
                return true;
            auto inv = damageableComponent->getInvulnerabilityRemaining();
            if (inv > 0) {
                damageableComponent->setInvulnerabilityRemaining(inv - elapsedTime);
                return inv - elapsedTime > 0;
            }
            return false;
        }), damageableEntities.end());

        std::vector<int> toDelete;

        for (auto &damagerEntity : damagerEntities) {
            auto lockedDamagerEntity = damagerEntity.lock();
            if (!lockedDamagerEntity)
                continue;
            auto damagerTr = std::dynamic_pointer_cast<ecs::components::TransformComponent>(lockedDamagerEntity->getComponent(ecs::components::TransformComponent::Version).lock());
            auto damagerDmg = std::dynamic_pointer_cast<ecs::components::DamagerComponent>(lockedDamagerEntity->getComponent(ecs::components::DamagerComponent::Version).lock());
            auto damagerCol = std::dynamic_pointer_cast<ecs::components::ColliderComponent>(lockedDamagerEntity->getComponent(ecs::components::ColliderComponent::Version).lock());
            if (!damagerDmg || !damagerCol)
                continue;
            auto damagerBasePos = (damagerTr) ? damagerTr->getPosition() : b12software::maths::Vector3D(0, 0, 0);
            auto damagerColWorldPos = b12software::maths::Vector2D(damagerBasePos.x, damagerBasePos.y) + damagerCol->getOffset();

            for (auto &damagedEntity : damageableEntities) {
                auto lockedDamagedEntity = damagedEntity.lock();
                if (!lockedDamagedEntity)
                    continue;
                auto damagedTr = std::dynamic_pointer_cast<ecs::components::TransformComponent>(lockedDamagedEntity->getComponent(ecs::components::TransformComponent::Version).lock());
                auto damagedDmg = std::dynamic_pointer_cast<ecs::components::DamageableComponent>(lockedDamagedEntity->getComponent(ecs::components::DamageableComponent::Version).lock());
                auto damagedCol = std::dynamic_pointer_cast<ecs::components::ColliderComponent>(lockedDamagedEntity->getComponent(ecs::components::ColliderComponent::Version).lock());
                if (!damagedDmg || !damagedCol)
                    continue;
                if (!damagedDmg->isAlive())
                    continue;
                if (!(damagerDmg->getDamageLayer() & damagedDmg->getDamageLayer()))
                    continue;
                auto damagedBasePos = (damagedTr) ? damagedTr->getPosition() : b12software::maths::Vector3D(0, 0, 0);
                auto damagedColWorldPos = b12software::maths::Vector2D(damagedBasePos.x, damagedBasePos.y) + damagedCol->getOffset();
                b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[" + lockedDamagerEntity->getName() + ":" + std::to_string(lockedDamagerEntity->getID()) + "] Check for collision with [" + lockedDamagedEntity->getName() + ":" + std::to_string(lockedDamagedEntity->getID()) + "]");
                if (collide(damagerColWorldPos, damagerCol->getSize(), damagedColWorldPos, damagedCol->getSize())) {
                    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[" + lockedDamagerEntity->getName() + ":" + std::to_string(lockedDamagerEntity->getID()) + "][" + lockedDamagedEntity->getName() + ":" + std::to_string(lockedDamagedEntity->getID()) + "] Collision");
                    damagedDmg->damage(damagerDmg->getDamages());
                    damagedDmg->setLastHitOwner(damagerDmg->getOwner());
                    if (damagerDmg->isDestroyOnHit()) {
                        toDelete.push_back(lockedDamagerEntity->getID());
                        break;
                    }
                }
            }
        }
        for (auto &id : toDelete) {
            auto entity = lockedWorld->popEntity(id);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[" + entity->getName() + ":" + std::to_string(entity->getID()) + "] Popped from world");
        }
    }
}

void systems::DamageSystem::start()
{
    ASystem::start();
    _elapsedTime = 0;
}

void systems::DamageSystem::stop()
{
    ASystem::stop();
    _elapsedTime = 0;
}
