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

namespace rtype {

    class CreateMainWindowEntities {

        CreateMainWindowEntities(std::weak_ptr<ecs::IWorld> world);

        ~CreateMainWindowEntities() = default;


    };
}

#endif //R_TYPE_CREATEMAINWINDOWENTITIES_HPP
