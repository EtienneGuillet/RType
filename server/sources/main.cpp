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
#include "logger/DefaultLogger.hpp"
#include "logger/StandardLogger.hpp"
#include "network/INetworkManager.hpp"
#include "network/asio/AsioNetworkManager.hpp"

namespace fs = std::filesystem;

namespace {
    volatile std::sig_atomic_t gSignalStatus;
}

static const std::string systemsFolder = "./server/systems";
static const std::string entitiesFolder = "./server/entities";

void signalHandler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    gSignalStatus = s;
}

std::unique_ptr<ecs::IECS> prepareGame(std::vector<ecs::DLLoader> &entities, std::vector<ecs::DLLoader> &systems)
{
    auto ecs = std::unique_ptr<ecs::IECS>(new ecs::ECS());

    return ecs;
}

void updateECS(std::shared_ptr<ecs::IWorld> &world)
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

    std::vector<ecs::DLLoader> entities, systems;
    auto ecs = std::unique_ptr<ecs::IECS>(new ecs::ECS());

    for (const auto &entry : fs::directory_iterator(entitiesFolder)) {
        std::cout << entry.path() << std::endl;
    }
    for (const auto &entry : fs::directory_iterator(systemsFolder)) {
        std::cout << entry.path() << std::endl;
    }

    while (gSignalStatus == 0) {
    }
    return 0;
}