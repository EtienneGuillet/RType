#include "ExampleSystem.hpp"
#include "../../commons/sources/logger/StandardLogger.hpp"

const ecs::Version ExampleSystem::Version = ecs::Version("ExampleSystem", 1, 0, 0, 0);

const ecs::Version &ExampleSystem::getType() const {
    return ExampleSystem::Version;
}

void ExampleSystem::tick(long deltatime) {
    auto logger = b12software::logger::StandardLogger(b12software::logger::LogLevelDebug);

    logger.log(b12software::logger::LogLevelDebug, "[ExampleSystem] TICK");
}