#include <components/IntComponent.hpp>
#include "ExampleSystem.hpp"
#include "logger/StandardLogger.hpp"

const ecs::Version ExampleSystem::Version = ecs::Version("ExampleSystem", 1, 0, 0, 0);

const ecs::Version &ExampleSystem::getType() const {
    return ExampleSystem::Version;
}

void ExampleSystem::tick([[maybe_unused]] long deltatime) {
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[ExampleSystem] Tick");
    auto world = _world.lock();

    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[ExampleSystem] Apply to each");
    world->applyToEach({IntComponent::Version}, [] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto intComponent = std::dynamic_pointer_cast<IntComponent>(components.front().lock());

        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[ExampleSystem] " + std::to_string(intComponent->operator++()));
    });
}