//
// Created by Lilian on 28/11/2019.
//

#include "EnemyAIApi.hpp"
#include "EnemyAISystem.hpp"

const ecs::Version systems::EnemyAIApi::Version = ecs::Version("API_AISystem", 1, 0, 0, 0);

const ecs::Version &systems::EnemyAIApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::EnemyAIApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new EnemyAISystem());
}
