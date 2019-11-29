/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.cpp
** File description:
** Created by tpautier,
*/

#include "CreateMainWindowEntities.hpp"

rtype::CreateMainWindowEntities::CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world)
{
    std::shared_ptr<ecs::IEntity> title = std::make_shared<ecs::Entity>("TitleSpriteEntity");

    world->pushEntity(std::static_pointer_cast<TitleSpriteEntity>(title));
}