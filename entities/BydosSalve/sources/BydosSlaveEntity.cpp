#include "BydosSlaveEntity.hpp"
#include <components/AIComponent/AIComponent.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/server/rigidbody/RigidbodyComponent.hpp>
#include <components/server/player/PlayerComponent.hpp>
#include <components/server/networkIdentity/NetworkIdentityComponent.hpp>
#include <components/server/displayable/DisplayableComponent.hpp>
#include <components/server/collider/ColliderComponent.hpp>
#include <components/server/damager/DamagerComponent.hpp>
#include <components/server/damageable/DamageableComponent.hpp>
#include <cmath>
#include <components/server/weapon/WeaponComponent.hpp>

BydosSlaveEntity::BydosSlaveEntity() : Entity("BydosSlaveEntity") {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    addComponent(std::make_shared<ecs::components::NetworkIdentityComponent>(getID()));
    addComponent(std::make_shared<ecs::components::DisplayableComponent>(rtype::ET_MONSTER_TYPE_BASE));
    addComponent(std::make_shared<ecs::components::ColliderComponent>(b12software::maths::Vector2D(50,50)));
    addComponent(std::make_shared<ecs::components::TransformComponent>(b12software::maths::Vector3D(1000.0f, 500.0f, 0.0f)));
    addComponent(std::make_shared<ecs::components::RigidbodyComponent>(200, b12software::maths::Vector2D(-20, 0)));
    addComponent(std::make_shared<ecs::components::DamagerComponent>(1, true, 0b1));
    addComponent(std::make_shared<ecs::components::DamageableComponent>(3, 3, 0, 0b10));
    addComponent(std::make_shared<ecs::components::WeaponComponent>());

    addComponent(std::make_shared<ecs::components::AIComponent>([this] (const std::shared_ptr<IEntity>& entity, std::shared_ptr<ecs::IWorld> world) {
        std::string prefixDebug = "[AI][" + entity->getName() + "][" + std::to_string(entity->getID()) + "]";
        auto rb = std::dynamic_pointer_cast<ecs::components::RigidbodyComponent>(entity->getComponent(ecs::components::RigidbodyComponent::Version).lock());
        auto transform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(entity->getComponent(ecs::components::TransformComponent::Version).lock());
        auto weapon = std::dynamic_pointer_cast<ecs::components::WeaponComponent>(entity->getComponent(ecs::components::WeaponComponent::Version).lock());

        if (rb) {
            auto playerPos = getPlayerPositions(world);
            float smallestDistance = -1.0f;
            auto ownPos = transform->getPosition();
            float distance = 0;

            for (auto &pos : playerPos) {
                distance = std::abs(pos.y - ownPos.y);
                //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "Distance: " + std::to_string(distance));
                if (distance < smallestDistance || smallestDistance == -1.0f) {
                    smallestDistance = distance;
                    auto direction = pos - ownPos;
                    rb->setDirection(b12software::maths::Vector2D(rb->getDirection().x, direction.y));
                    //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "Direction: " + std::to_string(direction.x) + ", " + std::to_string(direction.y));
                    //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "CapableDirection: " + std::to_string(rb->getDirection().x) + ", " + std::to_string(rb->getDirection().y));
                    if (distance <= 100) {
                        //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelWarn, prefixDebug + "TODO Shoot");
                        rb->setUps(50);
                    } else {
                        rb->setUps(200);
                    }
                }
            }
            //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "---------Scanned " + std::to_string(playerPos.size()) + " players ------");
            if (playerPos.empty()) {
                rb->setUps(0);
            } else {
                //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "Direction: " + std::to_string(rb->getDirection().x) + ", " + std::to_string(rb->getDirection().y));
                //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "OwnPos: " + std::to_string(ownPos.x) + ", " + std::to_string(ownPos.y) + ", " + std::to_string(ownPos.z));
                //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "---------------");
            }
        }
    }));
}

std::vector<b12software::maths::Vector3D> BydosSlaveEntity::getPlayerPositions(std::shared_ptr<ecs::IWorld> world) {
    auto players = world->getEntitiesWith({ecs::components::PlayerComponent::Version, ecs::components::TransformComponent::Version, ecs::components::DamageableComponent::Version});
    std::vector<b12software::maths::Vector3D> playerPositions;

    for (auto &player : players) {
        auto playerLocked = player.lock();

        if (playerLocked) {
            auto lockedTransform = playerLocked->getComponent({ecs::components::TransformComponent::Version}).lock();
            if (lockedTransform) {
                auto transform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(lockedTransform);

                if (transform) {
                    //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[AI][" + playerLocked->getName() + ":" + std::to_string(playerLocked->getID()) + "] Found " + std::to_string(transform->getPosition().x) + ", " + std::to_string(transform->getPosition().y) + ", " + std::to_string(transform->getPosition().z));
                    playerPositions.emplace_back(transform->getPosition());
                }
            }
        }
    }
    return playerPositions;
}
