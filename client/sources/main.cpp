/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

#include <ecs/IECS/IECS.hpp>
#include <memory>
#include <ecs/DLLoader/DLLoader.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>

/* Created the 07/11/2019 at 18:00 by julian.frabel@epitech.eu */

<<<<<<< HEAD
#include "logger/DefaultLogger.hpp"

int main()
{
    std::cout << "Loading default logger..." << std::endl;
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>());
    std::cout << "Default logger loaded!" << std::endl;


    std::unique_ptr<IECS> ecs = new ECS();
    std::unique_ptr<IWorld> world = ecs.createWorld();


    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    while () {
        end = std::chrono_system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < 1000) {
            start = std::chrono_system_clock::now();
            world.tick();
        }
    }
    return 0;
}
