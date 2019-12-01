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
    auto entityButtonRefresh = _ecs->createEntityFromAPI(ecs::Version("Entity_Button", 1, 0, 0, 0));
    auto background = _ecs->createEntityFromAPI(ecs::Version("Entity_Background", 1, 0, 0, 0));
    auto spriteBoxRooms = _ecs->createEntityFromAPI(ecs::Version("Entity_LobbyContainer", 1, 0, 0, 0));
    auto spriteBoxCreate = _ecs->createEntityFromAPI(ecs::Version("Entity_LobbyContainer", 1, 0, 0, 0));
    auto entityTextboxRoomName = _ecs->createEntityFromAPI(ecs::Version("Entity_Textbox", 0, 1, 0, 0));
    auto entityTextboxRoomPwd = _ecs->createEntityFromAPI(ecs::Version("Entity_Textbox", 0, 1, 0, 0));

    if (background) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(background->getComponent(rtype::TransformComponent::Version).lock());
        auto sprite = std::dynamic_pointer_cast<rtype::SpriteComponent>(background->getComponent(rtype::SpriteComponent::Version).lock());
        if (tr) {
            tr->setScale(3, 3);
        }
        if (sprite) {
            sprite->setRepeated(true);
        }
        lockedWorld->pushEntity(background);
    } else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find background");
    }
    if (spriteBoxCreate) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(spriteBoxCreate->getComponent(rtype::TransformComponent::Version).lock());
        if (tr) {
            tr->setPosition(100, 150, 0);
            tr->setScale(1.5, 0.7);
        }
        lockedWorld->pushEntity(spriteBoxCreate);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find spriteBoxCreate");
    }

    if (spriteBoxRooms) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(spriteBoxRooms->getComponent(rtype::TransformComponent::Version).lock());

        if (tr) {
            tr->setPosition(1120, 150, 0);
            tr->setScale(1.5, 0.3);
        }
        lockedWorld->pushEntity(spriteBoxRooms);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }

    if (entityButtonCreateRoom) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonCreateRoom->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonCreateRoom->getComponent(rtype::HoverComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonCreateRoom->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(1350, 600, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            hv->setHoverable(true);
            hv->setFunctionPointer(rtype::CreateMainWindowEntities::createRoom);
        }
        if (rt) {
            rt->setString("CREATE");
        }
        lockedWorld->pushEntity(entityButtonCreateRoom);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
    if (entityButtonRefresh) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonRefresh->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonRefresh->getComponent(rtype::HoverComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonRefresh->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(300, 900, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            hv->setHoverable(true);
            hv->setFunctionPointer(rtype::CreateMainWindowEntities::refreshRooms);
        }
        if (rt) {
            rt->setString("REFRESH");
        }
        lockedWorld->pushEntity(entityButtonRefresh);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find Entity_Button");
    }
    if (entityTextboxRoomName) {
        auto textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(entityTextboxRoomName->getComponent(rtype::TextComponent::Version).lock());
        auto transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextboxRoomName->getComponent(rtype::TransformComponent::Version).lock());
        auto hover = std::dynamic_pointer_cast<rtype::HoverComponent>(entityTextboxRoomName->getComponent(rtype::HoverComponent::Version).lock());
        auto updateText = std::dynamic_pointer_cast<rtype::UpdateTextComponent>(entityTextboxRoomName->getComponent(rtype::UpdateTextComponent::Version).lock());

        if (hover && updateText) {
            hover->setHoverable(true);
            updateText->setUpdatable(false);
        }
        if (transformComponent) {
            transformComponent->setPosition(1140, 200, 0);
            transformComponent->setScale(1.2, 1.2);
        }
        if (textComponent) {
            textComponent->setString("Room name : ");
        }
        lockedWorld->pushEntity(entityTextboxRoomName);
    }
    if (entityTextboxRoomPwd) {
        auto textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(entityTextboxRoomPwd->getComponent(rtype::TextComponent::Version).lock());
        auto transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextboxRoomPwd->getComponent(rtype::TransformComponent::Version).lock());
        auto hover = std::dynamic_pointer_cast<rtype::HoverComponent>(entityTextboxRoomPwd->getComponent(rtype::HoverComponent::Version).lock());
        auto updateText = std::dynamic_pointer_cast<rtype::UpdateTextComponent>(entityTextboxRoomPwd->getComponent(rtype::UpdateTextComponent::Version).lock());

        if (hover && updateText) {
            hover->setHoverable(true);
            updateText->setUpdatable(false);
        }
        if (transformComponent) {
            transformComponent->setPosition(1140, 350, 0);
            transformComponent->setScale(1.2, 1.2);
        }
        if (textComponent) {
            textComponent->setString("Room password : ");
        }
        lockedWorld->pushEntity(entityTextboxRoomPwd);
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
    auto entityTextboxUsername = _ecs->createEntityFromAPI(ecs::Version("Entity_Textbox", 0, 1, 0, 0));
    auto entityTextboxPort = _ecs->createEntityFromAPI(ecs::Version("Entity_Textbox", 0, 1, 0, 0));
    auto entityTextboxAddress = _ecs->createEntityFromAPI(ecs::Version("Entity_Textbox", 0, 1, 0, 0));
    auto entityTextInputUsername = _ecs->createEntityFromAPI(ecs::Version("Entity_textInput", 1, 0, 0, 0));
    auto entityTextInputPort = _ecs->createEntityFromAPI(ecs::Version("Entity_textInput", 1, 0, 0, 0));
    auto entityTextInputAddress = _ecs->createEntityFromAPI(ecs::Version("Entity_textInput", 1, 0, 0, 0));

    if (entityTitle) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTitle->getComponent(rtype::TransformComponent::Version).lock());

        if (tr) {
            tr->setPosition(550, -200, 0);
            tr->setScale(2, 2);
        }
        lockedWorld->pushEntity(entityTitle);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
    if (entityTextboxUsername) {
        auto textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(entityTextboxUsername->getComponent(rtype::TextComponent::Version).lock());
        auto transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextboxUsername->getComponent(rtype::TransformComponent::Version).lock());
        auto hover = std::dynamic_pointer_cast<rtype::HoverComponent>(entityTextboxUsername->getComponent(rtype::HoverComponent::Version).lock());
        auto updateText = std::dynamic_pointer_cast<rtype::UpdateTextComponent>(entityTextboxUsername->getComponent(rtype::UpdateTextComponent::Version).lock());

        if (hover && updateText) {
            hover->setHoverable(true);
            updateText->setUpdatable(false);
        }
        if (transformComponent) {
            transformComponent->setPosition(50, 400, 0);
            transformComponent->setScale(1.5, 1.5);
        }
        if (textComponent) {
            textComponent->setString("Username :      ");
        }
    }
    if (entityTextInputUsername) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextInputUsername->getComponent(rtype::TransformComponent::Version).lock());
        if (tr) {
            tr->setPosition(360, 390, 0);
            tr->setScale(1, 1);
        }
        lockedWorld->pushEntity(entityTextInputUsername);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
    if (entityTextInputPort) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextInputPort->getComponent(rtype::TransformComponent::Version).lock());
        if (tr) {
            tr->setPosition(230, 540, 0);
            tr->setScale(1, 1);
        }
        lockedWorld->pushEntity(entityTextInputPort);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
    if (entityTextInputAddress) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextInputAddress->getComponent(rtype::TransformComponent::Version).lock());
        if (tr) {
            tr->setPosition(370, 690, 0);
            tr->setScale(1, 1);
        }
        lockedWorld->pushEntity(entityTextInputAddress);
    }
    else {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "could not find TitleSprite_entity");
    }
    lockedWorld->pushEntity(entityTextboxUsername);
    if (entityTextboxPort) {
        auto textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(entityTextboxPort->getComponent(rtype::TextComponent::Version).lock());
        auto transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextboxPort->getComponent(rtype::TransformComponent::Version).lock());
        auto hover = std::dynamic_pointer_cast<rtype::HoverComponent>(entityTextboxPort->getComponent(rtype::HoverComponent::Version).lock());
        auto updateText = std::dynamic_pointer_cast<rtype::UpdateTextComponent>(entityTextboxPort->getComponent(rtype::UpdateTextComponent::Version).lock());

        if (hover && updateText) {
            hover->setHoverable(true);
            updateText->setUpdatable(false);
        }
        if (transformComponent) {
            transformComponent->setPosition(50, 550, 0);
            transformComponent->setScale(1.5, 1.5);
        }
        if (textComponent) {
            textComponent->setString("Port :      ");
        }
    }
    lockedWorld->pushEntity(entityTextboxPort);
    if (entityTextboxAddress) {
        auto textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(entityTextboxAddress->getComponent(rtype::TextComponent::Version).lock());
        auto transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(entityTextboxAddress->getComponent(rtype::TransformComponent::Version).lock());
        auto hover = std::dynamic_pointer_cast<rtype::HoverComponent>(entityTextboxAddress->getComponent(rtype::HoverComponent::Version).lock());
        auto updateText = std::dynamic_pointer_cast<rtype::UpdateTextComponent>(entityTextboxAddress->getComponent(rtype::UpdateTextComponent::Version).lock());

        if (hover && updateText) {
            hover->setHoverable(true);
            updateText->setUpdatable(false);
        }
        if (transformComponent) {
            transformComponent->setPosition(50, 700, 0);
            transformComponent->setScale(1.5, 1.5);
        }
        if (textComponent) {
            textComponent->setString("IP address :      ");
        }
    }
    lockedWorld->pushEntity(entityTextboxAddress);
    if (entityButtonPlay) {
        auto tr = std::dynamic_pointer_cast<rtype::TransformComponent>(entityButtonPlay->getComponent(rtype::TransformComponent::Version).lock());
        auto hv = std::dynamic_pointer_cast<rtype::HoverComponent>(entityButtonPlay->getComponent(rtype::HoverComponent::Version).lock());
        auto rt = std::dynamic_pointer_cast<rtype::TextComponent>(entityButtonPlay->getComponent(rtype::TextComponent::Version).lock());
        if (tr) {
            tr->setPosition(350, 900, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            hv->setHoverable(true);
            hv->setFunctionPointer(rtype::CreateMainWindowEntities::tryToConnect);
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
            tr->setPosition(1350, 900, 0);
            tr->setScale(2, 2);
        }
        if (hv) {
            hv->setHoverable(true);
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
    _isInRooms = false;
    _world = world;
    _ecs = &ecs;
    menuSceneLaunch();
}

void rtype::CreateMainWindowEntities::tryToConnect()
{
    auto lockedWorld = _world.lock();

    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::GameManagerComponent::Version}, []([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            auto gm = std::dynamic_pointer_cast<rtype::GameManagerComponent>(components[0].lock());
            if (gm) {
                gm->startConnecting();
            }
        });
    }
}

void rtype::CreateMainWindowEntities::checkForUpdateScene()
{
    auto lockedWorld = _world.lock();

    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::GameManagerComponent::Version}, [this]([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            auto gm = std::dynamic_pointer_cast<rtype::GameManagerComponent>(components[0].lock());

            if (gm) {
                if (!gm->getState().isTryingToConnected() && gm->getState().isConnnected() && !_isInRooms) {
                    roomSceneLaunch();
                    _isInRooms = true;
                }
            }
        });
    }
}

void rtype::CreateMainWindowEntities::createRoom()
{
    auto lockedWorld = _world.lock();

    if (!lockedWorld) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "Error locked world");
        return;
    }
    lockedWorld->applyToEach({rtype::GameManagerComponent::Version}, []([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto gm = std::dynamic_pointer_cast<rtype::GameManagerComponent>(components[0].lock());
        if (gm) {
            //todo create une room
        }
    });
}

void rtype::CreateMainWindowEntities::refreshRooms()
{
    auto lockedWorld = _world.lock();

    if (!lockedWorld) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, "Error locked world");
        return;
    }
    lockedWorld->applyToEach({rtype::GameManagerComponent::Version}, []([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        auto gm = std::dynamic_pointer_cast<rtype::GameManagerComponent>(components[0].lock());
        if (gm) {
            //gm->getState().
        }
    });
}

