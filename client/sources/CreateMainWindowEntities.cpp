/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.cpp
** File description:
** Created by tpautier,
*/

#include "CreateMainWindowEntities.hpp"

rtype::CreateMainWindowEntities::CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world, ecs::IECS &ecs)
{
    auto entity = ecs.createEntityFromAPI(ecs::Version("Entity_TitleSprite", 0, 1, 0, 0));

    if (entity) {
        world->pushEntity(entity);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
}
