#include "CleanEntitiesSystemApi.hpp"
#include "CleanEntitiesSystem.hpp"

const ecs::Version CleanEntitiesSystemAPI::Version = ecs::Version("System_Example", 1, 0, 0, 0);

const ecs::Version &CleanEntitiesSystemAPI::getVersion() const {
    return CleanEntitiesSystemAPI::Version;
}

std::shared_ptr <ecs::ISystem> CleanEntitiesSystemAPI::createNewSystem() const {
    return std::shared_ptr<ecs::ISystem>(new CleanEntitiesSystem);
}
