/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponSystem.cpp
*/

/* Created the 28/11/2019 at 11:12 by julian.frabel@epitech.eu */

#include <ecs/IEntity/Entity.hpp>
#include <components/server/collider/ColliderComponent.hpp>
#include "WeaponSystem.hpp"
#include "components/server/player/PlayerComponent.hpp"
#include "components/server/weapon/WeaponComponent.hpp"
#include "components/server/displayable/DisplayableComponent.hpp"
#include "components/server/networkIdentity/NetworkIdentityComponent.hpp"
#include "components/server/damager/DamagerComponent.hpp"
#include "components/server/rigidbody/RigidbodyComponent.hpp"
#include "components/Transform/TransformComponent.hpp"

const ecs::Version systems::WeaponSystem::Version = ecs::Version("SYSTEM_WeaponSystem", 0, 0, 1, 0);

void systems::WeaponSystem::tick(long deltatime)
{
    auto lockedWorld = _world.lock();
    if (!lockedWorld)
        return;
    lockedWorld->applyToEach(
        {ecs::components::PlayerComponent::Version, ecs::components::WeaponComponent::Version},
        [deltatime, &lockedWorld](std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            auto lockedPlayer = std::dynamic_pointer_cast<ecs::components::PlayerComponent>(components[0].lock());
            auto lockedWeapon = std::dynamic_pointer_cast<ecs::components::WeaponComponent>(components[1].lock());
            auto lockedEntity = entity.lock();
            if (!lockedPlayer || !lockedWeapon || !lockedEntity)
                return;
            float newCharge = lockedPlayer->getCharge() + lockedPlayer->isShotPressed() * lockedWeapon->getRps() * deltatime / 1000.0f;
            if (newCharge > 100.0)
                newCharge = 100.0;
            lockedPlayer->setCharge(newCharge);
            if (!lockedPlayer->isReleased())
                return;
            auto charge = lockedPlayer->getCharge();
            int shotLevel = 0;
            if (charge >= 30.0 && charge < 60.0) {
                shotLevel = 1;
            } else if (charge >= 60.0f && charge < 90.0f) {
                shotLevel = 2;
            } else if (charge >= 90.0) {
                shotLevel = 3;
            }
            lockedPlayer->setCharge(0);
            if (shotLevel == 0)
                return;
            auto parentTr = std::dynamic_pointer_cast<ecs::components::TransformComponent>(lockedEntity->getComponent(ecs::components::TransformComponent).lock());
            auto basePos = (parentTr) ? parentTr->getPosition() : b12software::maths::Vector3D(0, 0, 0);
            std::shared_ptr<ecs::IEntity> shotEntity = std::make_shared<ecs::Entity>("playerShot");
            auto networkIdComp = std::make_shared<ecs::components::NetworkIdentityComponent>(shotEntity->getID());
            shotEntity->addComponent(std::dynamic_pointer_cast<ecs::IComponent>(networkIdComp));
            auto transformComp = std::make_shared<ecs::components::TransformComponent>(basePos);
            shotEntity->addComponent(std::dynamic_pointer_cast<ecs::IComponent>(transformComp));
            auto colliderComp = std::make_shared<ecs::components::ColliderComponent>();
            shotEntity->addComponent(std::dynamic_pointer_cast<ecs::IComponent>(colliderComp));
            auto rigidBodyComp = std::make_shared<ecs::components::RigidbodyComponent>(1, b12software::maths::Vector2D(1, 0));
            shotEntity->addComponent(std::dynamic_pointer_cast<ecs::IComponent>(rigidBodyComp));
            auto damagerComp = std::make_shared<ecs::components::DamagerComponent>(shotLevel, true, 0b10);
            shotEntity->addComponent(std::dynamic_pointer_cast<ecs::IComponent>(damagerComp));
            auto displayableComp = std::make_shared<ecs::components::DisplayableComponent>(rtype::ET_SHOOT_TYPE_BASIC_BASE + shotLevel * 30);
            shotEntity->addComponent(std::dynamic_pointer_cast<ecs::IComponent>(displayableComp));
            lockedWorld->pushEntity(shotEntity);
        }
    );
}

const ecs::Version &systems::WeaponSystem::getType() const
{
    return Version;
}
