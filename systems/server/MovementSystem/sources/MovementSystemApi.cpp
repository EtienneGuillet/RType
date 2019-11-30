/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** MovementSystemApi.cpp
*/

/* Created the 28/11/2019 at 03:28 by julian.frabel@epitech.eu */

#include "MovementSystemApi.hpp"
#include "MovementSystem.hpp"

const ecs::Version systems::MovementSystemApi::Version = ecs::Version("API_MovementSystemApi", 0, 0, 1, 0);

const ecs::Version &systems::MovementSystemApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::MovementSystemApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new MovementSystem());
}
