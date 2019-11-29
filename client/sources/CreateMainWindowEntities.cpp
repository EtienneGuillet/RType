/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.cpp
** File description:
** Created by tpautier,
*/

#include <components/TextComponent.hpp>
#include "CreateMainWindowEntities.hpp"

rtype::CreateMainWindowEntities::CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world, ecs::IECS &ecs)
{
    auto entityTitle = ecs.createEntityFromAPI(ecs::Version("Entity_TitleSprite", 0, 1, 0, 0));
    auto entityButtonPlay = ecs.createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));
    auto entityButtonQuit = ecs.createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));

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
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonPlay->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(850, 570, 0);
            tr->setScale(2, 2);
        }
        if (rt) {
            rt->setString("PLAY");
        }
        world->pushEntity(entityButtonPlay);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
    if (entityButtonQuit) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonQuit->getComponent(rtype::TransformComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonQuit->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(850, 670, 0);
            tr->setScale(2, 2);
        }
        if (rt) {
            rt->setString("QUIT");
        }
        world->pushEntity(entityButtonQuit);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
}
