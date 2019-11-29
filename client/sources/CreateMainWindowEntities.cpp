/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.cpp
** File description:
** Created by tpautier,
*/

#include "CreateMainWindowEntities.hpp"

void rtype::CreateMainWindowEntities::GameScene()
{

}

void rtype::CreateMainWindowEntities::RoomScene()
{

}

void rtype::CreateMainWindowEntities::MenuScene()
{

}

rtype::CreateMainWindowEntities::CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world, ecs::IECS &ecs)
{
    auto entityTitle = ecs.createEntityFromAPI(ecs::Version("Entity_TitleSprite", 0, 1, 0, 0));
    auto entityButtonPlay = ecs.createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));

    if (entityTitle) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTitle->getComponent(rtype::TransformComponent::Version).lock());
        if (tr) {
            tr->setPosition(550, 0, 0);
            tr->setScale(2, 2);
        }
        world->pushEntity(entityTitle);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
    if (entityButtonPlay) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonPlay->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonPlay->getComponent(rtype::HoverComponent::Version).lock());
        if (tr) {
            tr->setPosition(0, 0, 0);
            tr->setScale(2, 2);
        }
        hv->setFunctionPointer(&rtype::CreateMainWindowEntities::RoomScene);
        world->pushEntity(entityButtonPlay);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
}
