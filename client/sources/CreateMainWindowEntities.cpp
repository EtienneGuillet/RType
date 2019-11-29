/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.cpp
** File description:
** Created by tpautier,
*/

#include "CreateMainWindowEntities.hpp"

rtype::CreateMainWindowEntities::CreateMainWindowEntities(std::weak_ptr<ecs::IWorld> world)
{
    auto lockedWorld = world.lock();

    if (lockedWorld) {
        //lockedWorld->pushEntity();
    }
}