/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

#include <ecs/IECS/IECS.hpp>
#include <memory>
#include <ecs/DLLoader/DLLoader.hpp>
#include <ecs/IECS/ECS.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <chrono>

int main(int ac, char **av)
{
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
    auto exampleSystem = exampleSystemAPI->createNewSystem();

    auto ecs = std::unique_ptr<ecs::IECS>(new ecs::ECS());
    auto world = ecs->createWorld();

    world->addSystem(exampleSystem);
    world->pushEntity(exampleEntity);

    auto start = std::chrono::system_clock::now();
    auto end = start;
    while (1) {
        end = std::chrono::system_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (deltaTime < 1000) {
            start = std::chrono::system_clock::now();
            world->tick(deltaTime);
        }
    }
    return 0;
}
