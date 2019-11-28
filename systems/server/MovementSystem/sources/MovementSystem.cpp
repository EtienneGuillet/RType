/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** MovementSystem.cpp
*/

/* Created the 28/11/2019 at 03:28 by julian.frabel@epitech.eu */

#include <cmath>
#include <logger/DefaultLogger.hpp>
#include "MovementSystem.hpp"
#include "components/server/rigidbody/RigidbodyComponent.hpp"
#include "components/Transform/TransformComponent.hpp"

const ecs::Version systems::MovementSystem::Version = ecs::Version("SYSTEM_MovementSystem", 0, 0, 1, 0);

void systems::MovementSystem::tick(long deltatime)
{
    auto lockedWorld = _world.lock();
    if (lockedWorld) {
        lockedWorld->applyToEach(
            {ecs::components::RigidbodyComponent::Version, ecs::components::TransformComponent::Version},
            [deltatime]([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
                auto rigidbodyomponent = std::dynamic_pointer_cast<ecs::components::RigidbodyComponent>(components[0].lock());
                auto transformComponent = std::dynamic_pointer_cast<ecs::components::TransformComponent>(components[1].lock());
                if (!rigidbodyomponent || ! transformComponent) {
                    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "[MovementSystem] Failed to retrieve component after casting. This should never happen.");
                    return;
                }
                auto dir = rigidbodyomponent->getDirection().normalized();
                auto movementVector = dir * rigidbodyomponent->getUps() * (deltatime / 1000.0f);
                auto newPos = transformComponent->getPosition() + b12software::maths::Vector3D(movementVector.x, movementVector.y, 0.0f);
                transformComponent->setPosition(newPos);
                if (rigidbodyomponent->shouldLookTowardsDirection()) {
                    auto rightVec = b12software::maths::Vector2D(1, 0);
                    auto angle = acosf(b12software::maths::Vector2D::Dot(dir, rightVec));
                    transformComponent->setRotation(b12software::maths::Vector2D(0, angle));
                }
            }
        );
    }
}

const ecs::Version &systems::MovementSystem::getType() const
{
    return Version;
}
