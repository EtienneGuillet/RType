/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** LifeSystemApi.cpp
*/

/* Created the 28/11/2019 at 06:08 by julian.frabel@epitech.eu */

#include "LifeSystemApi.hpp"
#include "LifeSystem.hpp"

const ecs::Version systems::LifeSystemApi::Version = ecs::Version("API_LifeSystemApi", 0, 0, 1, 0);

const ecs::Version &systems::LifeSystemApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::LifeSystemApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new LifeSystem());
}
