/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageSystemApi.cpp
*/

/* Created the 28/11/2019 at 04:28 by julian.frabel@epitech.eu */

#include "DamageSystemApi.hpp"
#include "DamageSystem.hpp"

const ecs::Version systems::DamageSystemApi::Version = ecs::Version("API_DamageSystemApi", 0, 0, 1, 0);

const ecs::Version &systems::DamageSystemApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::DamageSystemApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new DamageSystem());
}
