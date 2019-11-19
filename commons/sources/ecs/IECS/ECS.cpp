/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ECS.cpp
*/

/* Created the 19/11/2019 at 20:47 by julian.frabel@epitech.eu */

#include "ECS.hpp"

ecs::ECS::ECS()
{

}

ecs::ECS::~ECS()
{

}

std::shared_ptr<ecs::IWorld> ecs::ECS::createWorld()
{
    return std::shared_ptr<IWorld>();
}

std::shared_ptr<ecs::IEntity> ecs::ECS::createEntity(const ecs::Version &version)
{
    return std::shared_ptr<IEntity>();
}

bool ecs::ECS::knowSystem(const ecs::Version &version)
{
    return false;
}

bool ecs::ECS::knowEntity(const ecs::Version &version)
{
    return false;
}

bool ecs::ECS::knowSystems(const std::vector<Version> &versions)
{
    return false;
}

bool ecs::ECS::knowEntities(const std::vector<Version> &versions)
{
    return false;
}

void ecs::ECS::learnSystem(const std::shared_ptr<ISystemAPI> &api)
{

}

void ecs::ECS::learnEntity(const std::shared_ptr<IEntityAPI> &api)
{

}

std::shared_ptr<ecs::ISystemAPI> &ecs::ECS::forgetSystem(const ecs::Version &version)
{
    return <#initializer#>;
}

std::shared_ptr<ecs::IEntity> &ecs::ECS::forgetEntity(const ecs::Version &version)
{
    return <#initializer#>;
}
