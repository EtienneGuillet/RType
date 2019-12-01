#include "sfmlSystemAPI.hpp"
#include "sfmlSystem.hpp"

const ecs::Version SfmlSystemAPI::Version = ecs::Version("System_Sfml", 0, 1, 0, 0);

const ecs::Version &SfmlSystemAPI::getVersion() const {
    return SfmlSystemAPI::Version;
}

std::shared_ptr <ecs::ISystem> SfmlSystemAPI::createNewSystem() const {
    return std::shared_ptr<ecs::ISystem>(new SfmlSystem);
}
