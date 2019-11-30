//
// Created by Lilian on 28/11/2019.
//

#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include "EnemySpawnerSystem.hpp"

const ecs::Version systems::EnemySpawnerSystem::Version = ecs::Version("SYSTEM_EnemySpawner", 1, 0, 0, 0);

systems::EnemySpawnerSystem::EnemySpawnerSystem() : ASystem(), _elapsedTime(0), _computeEvery(100) {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
}

void systems::EnemySpawnerSystem::tick(long deltatime) {
    _elapsedTime += deltatime;
    if (_elapsedTime >= _computeEvery) {
        auto lockedWorld = _world.lock();

        if (lockedWorld) {
            auto lockedEcs = lockedWorld->getEcs().lock();

            if (lockedEcs) {
                auto entityAPIs = lockedEcs->getKnownEntities();
                for (auto &entityAPI : entityAPIs) {
                    if (entityAPI->isSpawnable()) {
                        computeSpawn(entityAPI, lockedWorld);
                    }
                }
            }
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

void systems::EnemySpawnerSystem::computeSpawn(std::shared_ptr<ecs::IEntityAPI> &entityApi, std::shared_ptr<ecs::IWorld> lockedWorld) {
    auto version = entityApi->getVersion();

    if (_timeBeforeSpawnMap.find(entityApi->getVersion()) == _timeBeforeSpawnMap.end()) {
        _timeBeforeSpawnMap[version] = entityApi->getSpawnFreq();
    } else {
        _timeBeforeSpawnMap[version] -= _elapsedTime;
        if (_timeBeforeSpawnMap[version] <= 0) {
            auto spawnedEntity = entityApi->createNewEntity();
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[" + version.getType() + "] Spawned");
            lockedWorld->pushEntity(spawnedEntity);
            _timeBeforeSpawnMap[version] += entityApi->getSpawnFreq();
        }
    }
}
