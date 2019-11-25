#include "AComponent.hpp"

void ecs::AComponent::setEntity(const std::weak_ptr<IEntity> &entity) {
    _entity = entity;
}

std::weak_ptr<ecs::IEntity> ecs::AComponent::getEntity() const {
    return _entity;
}
