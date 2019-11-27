#include "OmegatronSystemAPI.hpp"
#include "OmegatronSystem.hpp"

const ecs::Version OmegatronSystemAPI::Version = ecs::Version("System_Example", 1, 0, 0, 0);

const ecs::Version &OmegatronSystemAPI::getVersion() const {
    return OmegatronSystemAPI::Version;
}

std::shared_ptr <ecs::ISystem> OmegatronSystemAPI::createNewSystem() const {
    return std::shared_ptr<ecs::ISystem>(new OmegatronSystem);
}
