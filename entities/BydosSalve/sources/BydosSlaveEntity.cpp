#include "BydosSlaveEntity.hpp"
#include <components/AIComponent/AIComponent.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/server/rigidbody/RigidbodyComponent.hpp>
#include <components/server/player/PlayerComponent.hpp>

BydosSlaveEntity::BydosSlaveEntity() : Entity("BydosSlaveEntity") {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    addComponent(std::make_shared<ecs::components::TransformComponent>(b12software::maths::Vector3D(100.0f, 50.0f, 0.0f)));
    addComponent(std::make_shared<ecs::components::RigidbodyComponent>());
    addComponent(std::make_shared<ecs::components::AIComponent>([this] (const std::shared_ptr<IEntity>& entity, std::shared_ptr<ecs::IWorld> world) {
        std::string prefixDebug = "[AI][" + entity->getName() + "][" + std::to_string(entity->getID()) + "]";
        auto rb = std::dynamic_pointer_cast<ecs::components::RigidbodyComponent>(entity->getComponent(ecs::components::RigidbodyComponent::Version).lock());

        if (rb) {
            auto playerPos = getPlayerPositions(world);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug);

            for (auto &pos : playerPos) {
                b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "[" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) + "]");
            }
            rb->setDirection(b12software::maths::Vector2D(10, 0));
        }
    }));
}

std::vector<b12software::maths::Vector3D> BydosSlaveEntity::getPlayerPositions(std::shared_ptr<ecs::IWorld> world) {
    auto players = world->getEntitiesWith({ecs::components::PlayerComponent::Version, ecs::components::TransformComponent::Version});
    std::vector<b12software::maths::Vector3D> playerPositions;

    for (auto &player : players) {
        auto playerLocked = player.lock();

        if (playerLocked) {
            auto lockedTransform = playerLocked->getComponent({ecs::components::TransformComponent::Version}).lock();
            if (lockedTransform) {
                auto transform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(lockedTransform);

                if (transform) {
                    playerPositions.emplace_back(transform->getPosition());
                }
            }
        }
    }
    return playerPositions;
}
