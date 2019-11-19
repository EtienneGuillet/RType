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

int main(int ac, char **av)
{
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    if (ac != 3) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "./r-type_client path_to_example_entity path_to_example_system\n");
        return 1;
    }

    ecs::DLLoader exampleComponentLoader(av[1]);
    ecs::DLLoader exampleSystemLoader(av[2]);
    return 0;
}