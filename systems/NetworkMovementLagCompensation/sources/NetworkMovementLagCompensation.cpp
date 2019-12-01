/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkMovementLagCompensation.cpp
*/

/* Created the 01/12/2019 at 19:52 by julian.frabel@epitech.eu */

#include "NetworkMovementLagCompensation.hpp"
#include "components/TransformComponent.hpp"
#include "components/TransformNetworkLagCompensation.hpp"

const ecs::Version rtype::NetworkMovementLagCompensation::Version = ecs::Version("SYSTEM_NetworkMovementLagCompensation", 0, 0, 1, 0);

const ecs::Version &rtype::NetworkMovementLagCompensation::getType() const
{
    return Version;
}

void rtype::NetworkMovementLagCompensation::tick(long deltatime)
{
    auto lockedWorld = _world.lock();
    if (!lockedWorld)
        return;
    lockedWorld->applyToEach({rtype::TransformComponent::Version, rtype::TransformNetworkLagCompensation::Version},
        [&deltatime]([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            auto lockedTr = std::dynamic_pointer_cast<rtype::TransformComponent>(components[0].lock());
            auto lockedTrCompensation = std::dynamic_pointer_cast<rtype::TransformNetworkLagCompensation>(components[1].lock());
            if (!lockedTr || ! lockedTrCompensation)
                return;
            b12software::maths::Vector3D pos = b12software::maths::Vector3D(lockedTr->getPosition().x, lockedTr->getPosition().y, lockedTr->getPosition().z);
            auto newPos = pos + lockedTrCompensation->getDirection() * (deltatime / 1000.0f);
            lockedTr->setPosition(newPos.x, newPos.y, newPos.z);
        }
    );
}
