/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

#include <iostream>
#include <ecs/IECS/IECS.hpp>
#include <memory>
#include <ecs/DLLoader/DLLoader.hpp>
#include <ecs/IECS/ECS.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <chrono>
#include <csignal>

namespace {
    volatile std::sig_atomic_t gSignalStatus;
}

void signalHandler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    gSignalStatus = s;
}

int main(int ac, char **av)
{
    std::signal(SIGINT, signalHandler);

    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    if (ac != 3) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "./r-type_client path_to_example_entity path_to_example_system\n");
        return 1;
    }

    ecs::DLLoader exampleEntityLoader(av[1]);
    ecs::DLLoader exampleSystemLoader(av[2]);

    auto exampleEntityAPI = exampleEntityLoader.loadAPI<ecs::IEntityAPI>("entryPointEntityAPI");
    auto exampleSystemAPI = exampleSystemLoader.loadAPI<ecs::ISystemAPI>("entryPointSystemAPI");

    auto exampleEntity = exampleEntityAPI->createNewEntity();
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "ExampleEntity loaded");
    auto exampleEntity2 = exampleEntityAPI->createNewEntity();
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "ExampleEntity loaded");
    auto exampleSystem = exampleSystemAPI->createNewSystem();
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "ExampleSystem loaded");

    auto ecs = std::unique_ptr<ecs::IECS>(new ecs::ECS());
    auto world = ecs->createWorld();

    world->addSystem(exampleSystem);
    exampleSystem->setWorld(world);
    exampleSystem->start();
    world->pushEntity(exampleEntity);
    world->pushEntity(exampleEntity2);

    auto start = std::chrono::system_clock::now();
    auto end = start;
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Starting world");
    while (gSignalStatus == 0) {
        end = std::chrono::system_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (deltaTime >= 10) {
            start = std::chrono::system_clock::now();
            world->tick(deltaTime);
        }
    }
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Shutting down gracefully");
    return 0;
}
