//
// Created by Lilian on 28/11/2019.
//

#include "EnemySpawnerApi.hpp"
#include "EnemySpawnerSystem.hpp"

const ecs::Version systems::EnemySpawnerApi::Version = ecs::Version("API_EnemySpawner", 0, 0, 0, 0);

const ecs::Version &systems::EnemySpawnerApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::EnemySpawnerApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new EnemySpawnerSystem());
}
