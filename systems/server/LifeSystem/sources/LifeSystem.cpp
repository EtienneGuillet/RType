/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** LifeSystem.cpp
*/

/* Created the 28/11/2019 at 06:09 by julian.frabel@epitech.eu */

#include "LifeSystem.hpp"
#include "components/server/damageable/DamageableComponent.hpp"
#include "components/server/player/PlayerComponent.hpp"
#include "components/server/pointAwarder/PointAwarderComponent.hpp"
#include "components/Transform/TransformComponent.hpp"
#include "components/server/weapon/WeaponComponent.hpp"
#include "components/server/collider/ColliderComponent.hpp"
#include "components/server/rigidbody/RigidbodyComponent.hpp"
#include "components/server/displayable/DisplayableComponent.hpp"

const ecs::Version systems::LifeSystem::Version = ecs::Version("SYSTEM_LifeSystem", 0, 0, 1, 0);

void systems::LifeSystem::tick([[maybe_unused]]long deltatime)
{
    auto lockedWorld = _world.lock();
    if (lockedWorld) {
        std::vector<int> toDelete;
        lockedWorld->applyToEach(
            {ecs::components::DamageableComponent::Version},
            [&lockedWorld, &toDelete](std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
                auto damageableComp = std::dynamic_pointer_cast<ecs::components::DamageableComponent>(components[0].lock());
                if (!damageableComp || damageableComp->isAlive())
                    return;
                auto lockedEntity = entity.lock();
                if (!lockedEntity)
                    return;

                auto awardedEntityId = damageableComp->getLastHitOwner();
                if (awardedEntityId != 0) {
                    auto pointAwarderComp = std::dynamic_pointer_cast<ecs::components::PointAwarderComponent>(lockedEntity->getComponent(ecs::components::PointAwarderComponent::Version).lock());
                    if (pointAwarderComp) {
                        auto awardedEntity = lockedWorld->getEntityById(awardedEntityId).lock();
                        if (awardedEntity) {
                            auto playerComp = std::dynamic_pointer_cast<ecs::components::PlayerComponent>(awardedEntity->getComponent(ecs::components::PlayerComponent::Version).lock());
                            if (playerComp) {
                                playerComp->setScore(playerComp->getScore() + pointAwarderComp->getPoints());
                            }
                        }
                    }
                }

                auto playerComp = std::dynamic_pointer_cast<ecs::components::PlayerComponent>(lockedEntity->getComponent(ecs::components::PlayerComponent::Version).lock());
                if (!playerComp) {
                    toDelete.push_back(lockedEntity->getID());
                } else {
                    lockedEntity->removeComponent(ecs::components::DamageableComponent::Version);
                    lockedEntity->removeComponent(ecs::components::TransformComponent::Version);
                    lockedEntity->removeComponent(ecs::components::WeaponComponent::Version);
                    lockedEntity->removeComponent(ecs::components::ColliderComponent::Version);
                    lockedEntity->removeComponent(ecs::components::RigidbodyComponent::Version);
                    lockedEntity->removeComponent(ecs::components::DisplayableComponent::Version);
                }
            }
        );
        for (auto &id : toDelete) {
            lockedWorld->popEntity(id);
        }
    }
}

const ecs::Version &systems::LifeSystem::getType() const
{
    return Version;
}
