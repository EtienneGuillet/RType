#include "ExampleSystemApi.hpp"
#include "ExampleSystem.hpp"

const ecs::Version ExampleSystemAPI::Version = ecs::Version("System_Example", 1, 0, 0, 0);

const ecs::Version &ExampleSystemAPI::getVersion() const {
    return ExampleSystemAPI::Version;
}

std::shared_ptr <ecs::ISystem> ExampleSystemAPI::createNewSystem() const {
    return std::shared_ptr<ecs::ISystem>(new ExampleSystem);
}
