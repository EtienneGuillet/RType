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
#include <rtype/LibLoader/LibLoader.hpp>
#include "CreateMainWindowEntities.hpp"

namespace {
    volatile std::sig_atomic_t gSignalStatus;
}

void signalHandler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    gSignalStatus = s;
}

void runMain(const std::string &libsFolder)
{
    auto start = std::chrono::system_clock::now();
    auto end = start;
    auto ecs = std::unique_ptr<ecs::IECS>(new ecs::ECS());
    auto world = ecs->createWorld();
    auto libLoader = rtype::LibLoader(ecs, world, libsFolder);
    rtype::CreateMainWindowEntities MainWindow(world, *ecs);

    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Starting world");
    while (gSignalStatus == 0) {
        end = std::chrono::system_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (deltaTime >= 10) {
            start = std::chrono::system_clock::now();
            libLoader.checkForChanges();
            world->tick(deltaTime);
        }
    }
    world = std::shared_ptr<ecs::IWorld>();
    ecs = std::unique_ptr<ecs::IECS>();
}

int main(int ac, char **av)
{
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
    std::signal(SIGINT, signalHandler);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Logger and signal handler set");
    std::string libsFolder = "./client";

    if (ac > 1)
        libsFolder = av[1];
    try {
        runMain(libsFolder);
    } catch (b12software::exception::B12SoftwareException &e) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, e.what());
        return 84;
    } catch (std::exception &e) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, e.what());
        return 84;
    } catch (...) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelFatal, "An unknown error occurred.");
        return 84;
    }

    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Exit gracefully");
    return 0;
}