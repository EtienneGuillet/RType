#include "KamikazeEntity.hpp"
#include <components/AIComponent/AIComponent.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/server/rigidbody/RigidbodyComponent.hpp>
#include <components/server/player/PlayerComponent.hpp>
#include <cmath>
#include <components/server/damager/DamagerComponent.hpp>
#include <components/server/networkIdentity/NetworkIdentityComponent.hpp>
#include <components/server/collider/ColliderComponent.hpp>
#include <components/server/displayable/DisplayableComponent.hpp>
#include <components/server/damageable/DamageableComponent.hpp>

KamikazeEntity::KamikazeEntity() : Entity("KamikazeEntity") {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    addComponent(std::make_shared<ecs::components::NetworkIdentityComponent>(getID()));
    addComponent(std::make_shared<ecs::components::DisplayableComponent>(rtype::ET_MONSTER_TYPE_KAMIKAZE));
    addComponent(std::make_shared<ecs::components::ColliderComponent>(b12software::maths::Vector2D(5,5)));
    addComponent(std::make_shared<ecs::components::TransformComponent>(b12software::maths::Vector3D(100.0f, 50.0f, 0.0f)));
    addComponent(std::make_shared<ecs::components::RigidbodyComponent>());
    addComponent(std::make_shared<ecs::components::DamagerComponent>(1, true, 0b1));
    addComponent(std::make_shared<ecs::components::DamageableComponent>(1, 1, 0, 0b10));

    addComponent(std::make_shared<ecs::components::AIComponent>([this] (const std::shared_ptr<IEntity>& entity, std::shared_ptr<ecs::IWorld> world) {
        std::string prefixDebug = "[AI][" + entity->getName() + "][" + std::to_string(entity->getID()) + "]";
        auto rb = std::dynamic_pointer_cast<ecs::components::RigidbodyComponent>(entity->getComponent(ecs::components::RigidbodyComponent::Version).lock());
        auto transform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(entity->getComponent(ecs::components::TransformComponent::Version).lock());

        if (rb) {
            auto playerPos = getPlayerPositions(world);
            float smallestDistance = -1.0f;
            auto ownPos = transform->getPosition();
            float distance = 0;

            for (auto &pos : playerPos) {
                distance = std::sqrt(std::pow(pos.x + ownPos.x, 2) + std::pow(pos.y + ownPos.y, 2) + std::pow(pos.z + ownPos.z, 2));
                if (distance < smallestDistance || smallestDistance == -1.0f) {
                    auto direction = pos - ownPos;
                    rb->setDirection(b12software::maths::Vector2D(direction.x, direction.y));
                    rb->setUps(10);
                }
            }
            //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "---------Scanned " + std::to_string(playerPos.size()) + " players ------");
            if (playerPos.empty()) {
                rb->setUps(0);
            } else {
                //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "Direction: " + std::to_string(rb->getDirection().x) + ", " + std::to_string(rb->getDirection().y));
                //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "---------------");
            }
        }
    }));
}

std::vector<b12software::maths::Vector3D> KamikazeEntity::getPlayerPositions(std::shared_ptr<ecs::IWorld> world) {
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
