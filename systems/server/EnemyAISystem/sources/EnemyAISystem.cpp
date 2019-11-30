//
// Created by Lilian on 28/11/2019.
//

#include <components/AIComponent/AIComponent.hpp>
#include <logger/ILogger.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include "EnemyAISystem.hpp"

const ecs::Version systems::EnemyAISystem::Version = ecs::Version("SYSTEM_EnemyAI", 1, 0, 0, 0);

systems::EnemyAISystem::EnemyAISystem() : ASystem(), _elapsedTime(0), _computeEvery(50) {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
}

void systems::EnemyAISystem::tick(long deltatime) {
    _elapsedTime += deltatime;
    if (_elapsedTime >= _computeEvery) {
        auto lockedWorld = _world.lock();

        if (lockedWorld) {
            lockedWorld->applyToEach({ecs::components::AIComponent::Version}, [lockedWorld] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
                auto AIComponent = std::dynamic_pointer_cast<ecs::components::AIComponent>(components.front().lock());
                auto lockedEntity = entity.lock();
                AIComponent->operator ()(lockedEntity, lockedWorld);
            });
        }
        _elapsedTime -= _computeEvery;
    }
}

const ecs::Version &systems::EnemyAISystem::getType() const {
    return EnemyAISystem::Version;
}

void systems::EnemyAISystem::start() {
    ASystem::start();
}

void systems::EnemyAISystem::stop() {
    ASystem::stop();
}
