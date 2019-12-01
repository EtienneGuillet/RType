/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeEntityType.hpp
*/

/* Created the 27/11/2019 at 21:53 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEENTITYTYPE_HPP
#define R_TYPE_RTYPEENTITYTYPE_HPP

#include <cstdint>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @enum RTypeEntityType
     * @brief An enum describing the type of entity based on an id
     */
    enum RTypeEntityType : uint32_t {
        ET_UNKNOWN = 0,
        ET_PLAYER_1 = 1,
        ET_PLAYER_2 = 2,
        ET_PLAYER_3 = 3,
        ET_PLAYER_4 = 4,
        ET_SHOOT_TYPE_BASIC_BASE = 100, /*!< Anywhere from 100 - 199 is a basic shot the value indicate its size */
        ET_SHOOT_TYPE_BASIC_MAX = 199, /*!< Anywhere from 100 - 199 is a basic shot the value indicate its size */
        ET_BONUS_SHOOTING_SPEED_UP = 1000,
        ET_BONUS_SHOOTING_SPEED_DOWN = 1001,
        ET_BONUS_MOVING_SPEED_UP = 1000,
        ET_BONUS_MOVING_SPEED_DOWN = 1001,
        ET_MONSTER_TYPE_BASE = 100000, /*!< Above this value should be the monsters types */
        ET_MONSTER_TYPE_KAMIKAZE = 100001
    };
}

#endif //R_TYPE_RTYPEENTITYTYPE_HPP
