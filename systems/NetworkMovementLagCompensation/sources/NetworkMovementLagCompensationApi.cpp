/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkMovementLagCompensationApi.cpp
*/

/* Created the 01/12/2019 at 19:50 by julian.frabel@epitech.eu */

#include "NetworkMovementLagCompensationApi.hpp"
#include "NetworkMovementLagCompensation.hpp"

const ecs::Version rtype::NetworkMovementLagCompensationApi::Version = ecs::Version("API_NetworkMovementLagCompensation", 0, 0, 1, 0);

const ecs::Version &rtype::NetworkMovementLagCompensationApi::getVersion() const
{
    return Version;
}

std::shared_ptr<ecs::ISystem> rtype::NetworkMovementLagCompensationApi::createNewSystem() const
{
    return std::shared_ptr<ecs::ISystem>(new rtype::NetworkMovementLagCompensation());
}
