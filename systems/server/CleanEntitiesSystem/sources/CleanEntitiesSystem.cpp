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
            b12software::maths::Vector2D pos(transform->getPosition().x, transform->getPosition().y);
            if (lockedEntity->hasComponent(ecs::components::ColliderComponent::Version)) {
                auto collider = std::dynamic_pointer_cast<ecs::components::ColliderComponent>(lockedEntity->getComponent(ecs::components::ColliderComponent::Version).lock());
                auto rm = true;

                if (!collider)
                    return;
                auto size = collider->getSize();
                std::array<b12software::maths::Vector2D, 4> rect = {
                        b12software::maths::Vector2D(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f),
                        b12software::maths::Vector2D(pos.x + size.x * 0.5f, pos.y - size.y * 0.5f),
                        b12software::maths::Vector2D(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
                        b12software::maths::Vector2D(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f)
                };
                for (auto &point : rect) {
                    if (!(point.x < 0 || point.y < 0 || point.x > 1000 || point.y > 1000)) {
                        rm = false;
                    }
                }
                if (rm) {
                    //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "[" + lockedEntity->getName() + ":" + std::to_string(lockedEntity->getID()) +"] To clean");
                    toDelete.push_back(lockedEntity->getID());
                }
            } else {
                if (pos.x < 0 || pos.y < 0 || pos.x > 1000 || pos.y > 1000) {
                    //b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, prefixDebug + "[" + lockedEntity->getName() + ":" + std::to_string(lockedEntity->getID()) +"] To clean");
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
