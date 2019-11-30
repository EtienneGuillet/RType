/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponSystemApi.cpp
*/

/* Created the 28/11/2019 at 11:10 by julian.frabel@epitech.eu */

#include "WeaponSystemApi.hpp"
#include "WeaponSystem.hpp"

const ecs::Version systems::WeaponSystemApi::Version = ecs::Version("API_WeaponSystemApi", 0, 0, 1, 0);

const ecs::Version &systems::WeaponSystemApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> systems::WeaponSystemApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new WeaponSystem());
}
