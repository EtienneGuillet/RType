#include "AIComponent.hpp"

const ecs::Version ecs::components::AIComponent::Version = ecs::Version("COMPONENT_AIComponent", 1, 0, 0, 0);

ecs::components::AIComponent::AIComponent(Handler handler) : _handler(handler) {
}

ecs::components::AIComponent::AIComponent(const AIComponent &other) : _handler(other._handler) {
}

ecs::components::AIComponent &ecs::components::AIComponent::operator =(const AIComponent &rhs) {
    _handler = rhs._handler;
    return *this;
}

const ecs::Version &ecs::components::AIComponent::getVersion() const
{
    return Version;
}

void ecs::components::AIComponent::operator ()(std::shared_ptr<IEntity> &entity) {
    _handler(entity);
}