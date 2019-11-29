/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** World.cpp
*/

/* Created the 19/11/2019 at 21:56 by julian.frabel@epitech.eu */

#include <logger/DefaultLogger.hpp>
#include <ecs/exceptions/ECSException.hpp>
#include <ecs/IECS/IECS.hpp>
#include "World.hpp"

ecs::World::World(std::weak_ptr<ecs::IECS> ecs)
    : _entities(), _systems(), _ecs(ecs) {

}

ecs::World::~World()
{

}

void ecs::World::tick(long deltatime)
{
    for (auto &system : _systems) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[World] Tick (dt=" + std::to_string(deltatime) + ")");
        system->tick(deltatime);
    }
}

std::weak_ptr<ecs::IEntity> ecs::World::pushEntity(const std::shared_ptr<IEntity> &entity)
{
    if (!entity) {
        throw ECSException("Can not add an invalid entity", WHERE);
    }
    return _entities.emplace_back(entity);
}

std::shared_ptr<ecs::IEntity> ecs::World::popEntity(int id)
{
    for (auto it = _entities.begin(); it != _entities.end(); ++it) {
        if ((*it)->getID() == id) {
            std::shared_ptr<IEntity> elem = *it;
            _entities.erase(it);
            return elem;
        }
    }
    return std::shared_ptr<IEntity>();
}

std::vector<std::weak_ptr<ecs::IEntity>> ecs::World::getEntitiesWith(const std::vector<Version> &components) const
{
    std::vector<std::weak_ptr<IEntity>> ret;
    for (auto &entity : _entities) {
        if (entity->hasComponents(components)) {
            ret.emplace_back(entity);
        }
    }
    return ret;
}

void ecs::World::applyToEach(const std::vector<Version> &componentTypes, std::function<void(std::weak_ptr<IEntity>, std::vector<std::weak_ptr<IComponent>>)> toApply)
{
    for (auto &entity : _entities) {
        auto components = entity->getComponents(componentTypes);
        if (!components.empty()) {
            toApply(entity, components);
        }
    }
}

std::weak_ptr<ecs::ISystem> ecs::World::addSystem(const std::shared_ptr<ISystem> &system)
{
    if (!system) {
        throw ECSException("Can not add an invalid system", WHERE);
    }
    auto newSystem = _systems.emplace_back(system);
    newSystem->setWorld(weak_from_this());
    return newSystem;
}

void ecs::World::removeSystem(const ecs::Version &system)
{
    for (auto it = _systems.begin(); it != _systems.end(); ++it) {
        if ((*it)->getType() >= system) {
            _systems.erase(it);
            return;
        }
    }
}

std::weak_ptr<ecs::ISystem> ecs::World::getSystem(const ecs::Version &systemType)
{
    for (auto &system : _systems) {
        if (system->getType() >= systemType) {
            return system;
        }
    }
    return std::weak_ptr<ISystem>();
}

std::weak_ptr<ecs::IEntity> ecs::World::getEntityById(int id) const
{
    for (auto &entity : _entities) {
        if (entity->getID() == id) {
           return entity;
        }
    }
    return std::weak_ptr<IEntity>();
}

const std::weak_ptr<ecs::IECS> &ecs::World::getEcs() const {
    return _ecs;
}
