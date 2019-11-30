/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

#include <iostream>
#include <chrono>
#include <csignal>
#include <memory>
#include <thread>
#include "ecs/IECS/IECS.hpp"
#include "ecs/DLLoader/DLLoader.hpp"
#include "ecs/IECS/ECS.hpp"
#include "logger/DefaultLogger.hpp"
#include "logger/StandardLogger.hpp"
#include "rtype/LibLoader/LibLoader.hpp"
#include "components/GameManager/GameManagerComponent.hpp"
#include "CreateMainWindowEntities.hpp"
#include "RTypeNetworkClient.hpp"

namespace {
    volatile std::sig_atomic_t gSignalStatus;
}

void signalHandler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    gSignalStatus = s;
}

void fakeDatagramSequence(rtype::NetworkState &state, rtype::RTypeNetworkClient &networkClient) //todo remove me
{
    state.setServerHost("127.0.0.1");
    state.setServerPort(8080);
    state.connect("julian");
    while (!state.isConnnected()) {
        networkClient.update(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    state.getLobbyState().createLobby("Room1", "", 1);
    while (!state.getLobbyState().isInLobby()) {
        networkClient.update(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    while (!state.isInGame()) {
        networkClient.update(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void runMain(const std::string &libsFolder)
{
    bool shouldClose = false;
    rtype::NetworkState state;
    std::unique_ptr<rtype::RTypeNetworkClient> networkClient;
    try {
        networkClient = std::make_unique<rtype::RTypeNetworkClient>(state);
    } catch (b12software::exception::B12SoftwareException &e) {
        throw b12software::exception::B12SoftwareException(std::string("Fail to setup network ") + e.what(), WHERE);
    }
    auto start = std::chrono::system_clock::now();
    auto end = start;
    auto ecs = std::shared_ptr<ecs::IECS>(new ecs::ECS());
    auto world = ecs->createWorld();
    auto libLoader = rtype::LibLoader(ecs, world, libsFolder);

    auto gameManager = std::make_shared<ecs::Entity>("GameManager");
    gameManager->setShouldBeKeeped(true);
    gameManager->addComponent(std::shared_ptr<rtype::GameManagerComponent>(new rtype::GameManagerComponent(state, shouldClose)));
    world->pushEntity(gameManager);

    //Comment the first line and uncomment the second one to try the game
    rtype::CreateMainWindowEntities MainWindow(world, *ecs);
    //fakeDatagramSequence(state, *networkClient);

    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Starting world");
    while (gSignalStatus == 0 && !shouldClose) {
        end = std::chrono::system_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (deltaTime >= 10) {
            start = std::chrono::system_clock::now();
            libLoader.checkForChanges();
            MainWindow.checkForUpdateScene();
            world->tick(deltaTime);
            networkClient->update(deltaTime);
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