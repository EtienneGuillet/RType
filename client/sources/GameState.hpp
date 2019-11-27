/*
** EPITECH PROJECT, 2022
** GameState.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_GAMESTATE_HPP
#define R_TYPE_GAMESTATE_HPP

#include "EntitiesState.hpp"
#include <vector>

namespace rtype {

    class GameState {

        public:

        GameState();

        ~GameState();

        

        private:

        std::vector<rtype::EntitiesState> _entities;
    };
}

#endif //R_TYPE_GAMESTATE_HPP
