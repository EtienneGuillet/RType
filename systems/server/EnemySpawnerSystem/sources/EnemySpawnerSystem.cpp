//
// Created by Lilian on 28/11/2019.
//

#include "EnemySpawnerSystem.hpp"

const ecs::Version systems::EnemySpawnerSystem::Version = ecs::Version("SYSTEM_EnemySpawner", 1, 0, 0, 0);

systems::EnemySpawnerSystem::EnemySpawnerSystem() : ASystem(), _elapsedTime(0), _computeEvery(50) {
}

void systems::EnemySpawnerSystem::tick(long deltatime) {
    _elapsedTime += deltatime;
    if (_elapsedTime >= _computeEvery) {
        auto lockedWorld = _world.lock();

        if (lockedWorld) {
        }
        _elapsedTime -= _computeEvery;
    }
}

const ecs::Version &systems::EnemySpawnerSystem::getType() const {
    return EnemySpawnerSystem::Version;
}

void systems::EnemySpawnerSystem::start() {
    ASystem::start();
}

void systems::EnemySpawnerSystem::stop() {
    ASystem::stop();
}
