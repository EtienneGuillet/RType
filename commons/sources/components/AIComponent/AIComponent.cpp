#include "AIComponent.hpp"

const ecs::Version ecs::components::AIComponent::Version = ecs::Version("COMPONENT_AIComponent", 1, 0, 0, 0);

ecs::components::AIComponent::AIComponent() {
}

ecs::components::AIComponent::AIComponent(const AIComponent &other) {
}

ecs::components::AIComponent &ecs::components::AIComponent::operator =(const AIComponent &rhs) {
    return *this;
}

const ecs::Version &ecs::components::AIComponent::getVersion() const
{
    return Version;
}
