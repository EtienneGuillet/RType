/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Entity.cpp
*/

/* Created the 19/11/2019 at 20:55 by julian.frabel@epitech.eu */

#include "ecs/exceptions/ECSException.hpp"
#include "Entity.hpp"

ecs::IDGenerator ecs::Entity::Generator;

ecs::Entity::Entity(const std::string &name)
    : _id(Generator.generateNewID()), _name(name), _components()
{

}

ecs::Entity::~Entity()
{
    Generator.freeId(_id);
}

int ecs::Entity::getID() const
{
    return _id;
}

const std::string &ecs::Entity::getName() const
{
    return _name;
}

bool ecs::Entity::hasComponent(const ecs::Version &componentType) const
{
    for (auto &component : _components) {
        if (component->getVersion() >= componentType) {
            return true;
        }
    }
    return false;
}

bool ecs::Entity::hasComponents(const std::vector<Version> &componentTypes)
{
    for (auto &type : componentTypes) {
        if (!hasComponent(type))
            return false;
    }
    return true;
}

std::weak_ptr<ecs::IComponent> ecs::Entity::getComponent(const ecs::Version &componentType)
{
    for (auto &component : _components) {
        if (component->getVersion() >= componentType) {
            return component;
        }
    }
    return std::weak_ptr<IComponent>();
}

std::vector<std::weak_ptr<ecs::IComponent>> ecs::Entity::getComponents(const std::vector<Version> &componentTypes)
{
    std::vector<std::weak_ptr<IComponent>> result;

    for (auto &componentType : componentTypes) {
        auto component = getComponent(componentType);
        if (!component.lock()) {
            return std::vector<std::weak_ptr<IComponent>>();
        }
        result.push_back(component);
    }
    return result;
}

void ecs::Entity::addComponent(const std::shared_ptr<IComponent> &component)
{
    if (hasComponent(component->getVersion())) {
        throw ECSException("Entity already have a component of type " + component->getVersion().getType(), WHERE);
    }
    _components.emplace_back(component);
}

std::shared_ptr<ecs::IComponent> ecs::Entity::removeComponent(const ecs::Version &version)
{
    for (auto it = _components.begin(); it != _components.end(); ++it) {
        if ((*it)->getVersion() >= version) {
            std::shared_ptr<ecs::IComponent> elem = *it;
            _components.erase(it);
            return elem;
        }
    }
    return std::shared_ptr<ecs::IComponent>();
}
