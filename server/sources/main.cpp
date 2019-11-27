/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

/* Created the 07/11/2019 at 18:05 by julian.frabel@epitech.eu */

#include <csignal>
#include <iostream>
#include <memory>
#include <ecs/IWorld/IWorld.hpp>
#include <ecs/IWorld/World.hpp>
#include <ecs/DLLoader/DLLoader.hpp>
#include <ecs/IECS/IECS.hpp>
#include <ecs/IECS/ECS.hpp>
#include <filesystem>
#include <exception/B12SoftwareException.hpp>
#include <map>
#include <rtype/LibLoader/LibLoader.hpp>
#include "logger/DefaultLogger.hpp"
#include "logger/StandardLogger.hpp"
#include "network/INetworkManager.hpp"

namespace fs = std::filesystem;

namespace {
    volatile std::sig_atomic_t gSignalStatus;
}

void signalHandler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    gSignalStatus = s;
}

void updateWorld(std::shared_ptr<ecs::IWorld> &world)
{
    static auto start = std::chrono::system_clock::now();
    static auto end = start;

    end = std::chrono::system_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    if (deltaTime >= 10) {
        start = std::chrono::system_clock::now();
        world->tick(deltaTime);
    }
}

int main()
{
    std::signal(SIGINT, signalHandler);
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    auto ecs = std::unique_ptr<ecs::IECS>(new ecs::ECS());
    auto world = ecs->createWorld();
    auto libLoader = rtype::LibLoader(ecs, world, "./server");

    while (gSignalStatus == 0) {
        libLoader.checkForChanges();
        updateWorld(world);
    }
    return 0;
}