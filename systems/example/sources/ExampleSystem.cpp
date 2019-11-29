#include <components/Int/IntComponent.hpp>
#include "ExampleSystem.hpp"
#include "logger/StandardLogger.hpp"

const ecs::Version ExampleSystem::Version = ecs::Version("ExampleSystem", 1, 0, 0, 0);

const ecs::Version &ExampleSystem::getType() const {
    return ExampleSystem::Version;
}

void ExampleSystem::tick([[maybe_unused]]long deltatime) {
    auto world = _world.lock();

    world->applyToEach({IntComponent::Version}, [] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto intComponent = std::dynamic_pointer_cast<IntComponent>(components.front().lock());
        std::cout << "[ExampleSystem] " << std::to_string(intComponent->operator++()) << std::endl;
    });
}
