/*
** EPITECH PROJECT, 2022
** CreateMainWindowEntities.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_CREATEMAINWINDOWENTITIES_HPP
#define R_TYPE_CREATEMAINWINDOWENTITIES_HPP

#include <memory>
#include "ecs/IWorld/IWorld.hpp"
#include "../../entities/TitleSprite/sources/TitleSpriteEntity.hpp"
#include "../../entities/button/sources/ButtonEntity.hpp"
#include "../../entities/example/sources/ExampleEntity.hpp"

//todo changer le path absolue

namespace rtype {

    class CreateMainWindowEntities {

        public:

        CreateMainWindowEntities(std::shared_ptr<ecs::IWorld> &world);

        ~CreateMainWindowEntities() = default;

    };
}

#endif //R_TYPE_CREATEMAINWINDOWENTITIES_HPP
