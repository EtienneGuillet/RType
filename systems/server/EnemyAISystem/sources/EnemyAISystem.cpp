//
// Created by Lilian on 28/11/2019.
//

#include "EnemyAISystem.hpp"

const ecs::Version systems::EnemyAISystem::Version = ecs::Version("SYSTEM_EnemyAI", 1, 0, 0, 0);

systems::EnemyAISystem::EnemyAISystem() : ASystem(), _elapsedTime(0), _computeEvery(50) {
}

void systems::EnemyAISystem::tick(long deltatime) {
    _elapsedTime += deltatime;
    if (_elapsedTime >= _computeEvery) {
        auto lockedWorld = _world.lock();

        if (lockedWorld) {
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
