/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ECS.cpp
*/

/* Created the 19/11/2019 at 20:47 by julian.frabel@epitech.eu */

#include "ECS.hpp"
#include "ecs/IWorld/World.hpp"

ecs::ECS::ECS()
    : _systemsAPI(), _entitysAPI()
{

}

ecs::ECS::~ECS()
{

}

std::shared_ptr<ecs::IWorld> ecs::ECS::createWorld()
{
    return std::shared_ptr<IWorld>(new World());
}

std::shared_ptr<ecs::IEntity> ecs::ECS::createEntityFromAPI(const ecs::Version &version)
{
    for (auto &entityAPI : _entitysAPI) {
        if (entityAPI->getVersion() >= version) {
            return entityAPI->createNewEntity();
        }
    }
    return std::shared_ptr<IEntity>();
}

std::shared_ptr<ecs::ISystem> ecs::ECS::createSystemFromAPI(const ecs::Version &version)
{
    for (auto &systemAPI : _systemsAPI) {
        if (systemAPI->getVersion() >= version) {
            return systemAPI->createNewSystem();
        }
    }
    return std::shared_ptr<ISystem>();
}

bool ecs::ECS::knowSystem(const ecs::Version &version)
{
    for (auto &systemAPI : _systemsAPI) {
        if (systemAPI->getVersion() >= version) {
            return true;
        }
    }
    return false;
}

bool ecs::ECS::knowEntity(const ecs::Version &version)
{
    for (auto &entityAPI : _entitysAPI) {
        if (entityAPI->getVersion() >= version) {
            return true;
        }
    }
    return false;
}

bool ecs::ECS::knowSystems(const std::vector<Version> &versions)
{
    for (auto &version : versions) {
        if (!knowSystem(version))
            return false;
    }
    return true;
}

bool ecs::ECS::knowEntities(const std::vector<Version> &versions)
{
    for (auto &version : versions) {
        if (!knowEntity(version))
            return false;
    }
    return true;
}

void ecs::ECS::learnSystem(const std::shared_ptr<ISystemAPI> &api)
{
    _systemsAPI.emplace_back(api);
}

void ecs::ECS::learnEntity(const std::shared_ptr<IEntityAPI> &api)
{
    _entitysAPI.emplace_back(api);
}

std::shared_ptr<ecs::ISystemAPI> ecs::ECS::forgetSystem(const ecs::Version &version)
{
    for (auto it = _systemsAPI.begin(); it != _systemsAPI.end(); ++it) {
        if ((*it)->getVersion() >= version) {
            std::shared_ptr<ecs::ISystemAPI> elem = *it;
            _systemsAPI.erase(it);
            return elem;
        }
    }
    return std::shared_ptr<ecs::ISystemAPI>();
}

std::shared_ptr<ecs::IEntityAPI> ecs::ECS::forgetEntity(const ecs::Version &version)
{
    for (auto it = _entitysAPI.begin(); it != _entitysAPI.end(); ++it) {
        if ((*it)->getVersion() >= version) {
            std::shared_ptr<ecs::IEntityAPI> elem = *it;
            _entitysAPI.erase(it);
            return elem;
        }
    }
    return std::shared_ptr<ecs::IEntityAPI>();
}
