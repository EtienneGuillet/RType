/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_CREATEMAINWINDOWENTITIES_HPP
#define R_TYPE_CREATEMAINWINDOWENTITIES_HPP

#include <memory>
#include "ecs/IWorld/World.hpp"
#include "ecs/IECS/ECS.hpp"
#include "../../entities/TitleSprite/sources/TitleSpriteEntity.hpp"
#include "../../entities/button/sources/ButtonEntity.hpp"
#include "../../entities/example/sources/ExampleEntity.hpp"
#include <components/HoverComponent.hpp>
#include <components/ScrollComponent.hpp>
#include <components/UpdateTextComponent.hpp>
#include <components/MusicComponent.hpp>

//todo changer les path absolue

namespace rtype {

    class CreateMainWindowEntities {

    public:

        CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world, ecs::IECS &ecs);

        ~CreateMainWindowEntities() = default;

        static void closeByQuitButton(std::weak_ptr<ecs::IEntity> entity, std::weak_ptr<ecs::IWorld> world);
        static void tryToConnect(std::weak_ptr<ecs::IEntity> entity, std::weak_ptr<ecs::IWorld> world);
        static void createRoom(std::weak_ptr<ecs::IEntity> entity, std::weak_ptr<ecs::IWorld> world);
        static void refreshRooms(std::weak_ptr<ecs::IEntity> entity, std::weak_ptr<ecs::IWorld> world);
        static void roomSceneLaunch([[maybe_unused]]std::weak_ptr<ecs::IEntity> e, [[maybe_unused]]std::weak_ptr<ecs::IWorld> world);
        static void menuSceneLaunch();
        static void gameSceneLaunch();
        static void lobbySceneLaunch();
        void checkForUpdateScene();
    private:
        bool _isInLobbyOfRooms;
        bool _cleanCreateLobby;
        bool _cleanStartGame;
        static std::weak_ptr<ecs::IWorld> _world;
        static ecs::IECS *_ecs;
    };
}

#endif //R_TYPE_CREATEMAINWINDOWENTITIES_HPP
