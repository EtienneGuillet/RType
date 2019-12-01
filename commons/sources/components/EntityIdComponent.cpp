#include "EntityIdComponent.hpp"

const ecs::Version rtype::EntityIdComponent::Version = ecs::Version("EntityIdComponent", 0, 1, 0, 0);

rtype::EntityIdComponent::EntityIdComponent(int id)
    : _id(id)
{
}

void rtype::EntityIdComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
{
    _entity = entity;
}

const ecs::Version& rtype::EntityIdComponent::getVersion() const
{
    return rtype::EntityIdComponent::Version;
}

int rtype::EntityIdComponent::getID() const
{
    return _id;
}
