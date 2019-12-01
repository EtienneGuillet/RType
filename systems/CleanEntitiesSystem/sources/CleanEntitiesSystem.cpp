#include <components/Int/IntComponent.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <components/server/collider/ColliderComponent.hpp>
#include "CleanEntitiesSystem.hpp"
#include "logger/StandardLogger.hpp"

const ecs::Version CleanEntitiesSystem::Version = ecs::Version("CleanEntitiesSystem", 1, 0, 0, 0);

const ecs::Version &CleanEntitiesSystem::getType() const {
    return CleanEntitiesSystem::Version;
}

void CleanEntitiesSystem::tick(long deltatime) {
    std::string prefixDebug = "[" + Version.getType() + "]";
    auto world = _world.lock();

    std::vector<int> toDelete;
    world->applyToEach({ecs::components::TransformComponent::Version}, [&world, &toDelete, prefixDebug] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto transform = std::dynamic_pointer_cast<ecs::components::TransformComponent>(components.front().lock());
        auto lockedEntity = entity.lock();

        if (transform && lockedEntity) {
            if (lockedEntity->hasComponent(ecs::components::ColliderComponent::Version)) {
                std::array<b12software::maths::Vector2D, 4> rect;
            } else {
                b12software::maths::Vector2D pos(transform->getPosition().x, transform->getPosition().y);

                if (pos.x < 0 || pos.y < 0 || pos.x > 100 || pos.x > 100) {
                    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "[" + lockedEntity->getName() + ":" + std::to_string(lockedEntity->getID()) +"] To clean");
                    toDelete.push_back(lockedEntity->getID());
                }
            }
        }

    });
    for (auto &i : toDelete) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "[" + std::to_string(i) + "] Cleaned entity");
        world->popEntity(i);
    }
}

CleanEntitiesSystem::CleanEntitiesSystem() : ASystem() {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
}
