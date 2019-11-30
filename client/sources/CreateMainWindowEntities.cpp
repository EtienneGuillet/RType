/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.cpp
** File description:
** Created by tpautier,
*/

#include "components/TextComponent.hpp"
#include "components/GameManager/GameManagerComponent.hpp"
#include "CreateMainWindowEntities.hpp"

std::weak_ptr<ecs::IWorld> rtype::CreateMainWindowEntities::_world;
ecs::IECS *rtype::CreateMainWindowEntities::_ecs = nullptr;

void rtype::CreateMainWindowEntities::gameSceneLaunch()
{
    auto lockedWorld = _world.lock();
    if (!lockedWorld || _ecs == nullptr)
        return;
    auto entityBackground = _ecs->createEntityFromAPI(ecs::Version("Entity_Background", 1, 0, 0, 0));

    if (entityBackground) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityBackground->getComponent(rtype::TransformComponent::Version).lock());
        auto sprite = std::dynamic_pointer_cast<rtype::SpriteComponent>(entityBackground->getComponent(rtype::SpriteComponent::Version).lock());
        auto scroll = std::dynamic_pointer_cast<rtype::ScrollComponent>(entityBackground->getComponent(rtype::ScrollComponent::Version).lock());
        if (tr) {
            tr->setScale(3, 3);
        }
        if (sprite) {
            sprite->setRepeated(true);
        }
        if (scroll) {
            scroll->setScrollValues(sf::Vector2<float>(1, 0));
        }
        lockedWorld->pushEntity(entityBackground);
    }
}

void rtype::CreateMainWindowEntities::roomSceneLaunch()
{
    auto lockedWorld = _world.lock();
    if (!lockedWorld) {
        return;
    }
    lockedWorld->clearAllEntities();
    auto entityButtonCreateRoom = _ecs->createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));
    auto entityTextbox = _ecs->createEntityFromAPI(ecs::Version("Entity_Textbox", 0, 1, 0, 0));

    if (entityTextbox) {
        auto textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(entityTextbox->getComponent(rtype::TextComponent::Version).lock());
        auto transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextbox->getComponent(rtype::TransformComponent::Version).lock());
        if (transformComponent) {
            transformComponent->setPosition(850, 570, 0);
            transformComponent->setScale(2, 2);
        }
        if (textComponent) {
            textComponent->setString("Name:");
        }
    }
    lockedWorld->pushEntity(entityTextbox);

    if (entityButtonCreateRoom) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonCreateRoom->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonCreateRoom->getComponent(rtype::HoverComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonCreateRoom->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(700, 900, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "SET FUNCTION POINTER entityButtonPlay");
            hv->setFunctionPointer(rtype::CreateMainWindowEntities::roomSceneLaunch);
        }
        if (rt) {
            rt->setString("CREATE ROOM");
        }
        lockedWorld->pushEntity(entityButtonCreateRoom);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
}

void rtype::CreateMainWindowEntities::closeByQuitButton()
{
    auto lockedWorld = _world.lock();

    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::GameManagerComponent::Version}, []([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            auto gm = std::dynamic_pointer_cast<rtype::GameManagerComponent>(components[0].lock());
            if (gm) {
                gm->getShouldClose() = true;
            }
        });
    }
}

void rtype::CreateMainWindowEntities::menuSceneLaunch()
{
    auto lockedWorld = _world.lock();
    if (!lockedWorld || _ecs == nullptr)
        return;

    auto entityTitle = _ecs->createEntityFromAPI(ecs::Version("Entity_TitleSprite", 0, 1, 0, 0));
    auto entityButtonPlay = _ecs->createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));
    auto entityButtonQuit = _ecs->createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));

    if (entityTitle) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTitle->getComponent(rtype::TransformComponent::Version).lock());
        if (tr) {
            tr->setPosition(550, 0, 0);
            tr->setScale(2, 2);
        }
        lockedWorld->pushEntity(entityTitle);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
    if (entityButtonPlay) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonPlay->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonPlay->getComponent(rtype::HoverComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonPlay->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(850, 570, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "SET FUNCTION POINTER entityButtonPlay");
            hv->setFunctionPointer(rtype::CreateMainWindowEntities::roomSceneLaunch);
        }
        if (rt) {
            rt->setString("PLAY");
        }
        lockedWorld->pushEntity(entityButtonPlay);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
    if (entityButtonQuit) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonQuit->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonQuit->getComponent(rtype::HoverComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonQuit->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(850, 670, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            hv->setFunctionPointer(rtype::CreateMainWindowEntities::closeByQuitButton);
        }
        if (rt) {
            rt->setString("QUIT");
        }
        lockedWorld->pushEntity(entityButtonQuit);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
}

rtype::CreateMainWindowEntities::CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world, ecs::IECS &ecs)
{
    _world = world;
    _ecs = &ecs;
    roomSceneLaunch();
}
