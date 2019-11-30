//
// Created by Lilian on 29/11/2019.
//

#include <ecs/IECS/IECS.hpp>
#include <ecs/IECS/ECS.hpp>
#include <rtype/LibLoader/LibLoader.hpp>
#include <thread>
#include <csignal>

extern std::sig_atomic_t gSignalStatus;


void runGame(std::string libsFolder)
{
    std::shared_ptr<ecs::IECS> ecs = std::make_shared<ecs::ECS>();
    auto world = ecs->createWorld();
    auto libLoader = rtype::LibLoader(ecs, world, libsFolder);
    auto start = std::chrono::system_clock::now();
    auto end = start;

    while (gSignalStatus == 0) {
            end = std::chrono::system_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (deltaTime >= 10) {
            libLoader.checkForChanges();
            start = std::chrono::system_clock::now();
            world->tick(deltaTime);
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    world = std::shared_ptr<ecs::IWorld>();
    ecs = std::unique_ptr<ecs::IECS>();
}
