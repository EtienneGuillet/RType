/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ClientState.hpp
*/

/* Created the 25/11/2019 at 11:32 by julian.frabel@epitech.eu */

#ifndef R_TYPE_CLIENTSTATE_HPP
#define R_TYPE_CLIENTSTATE_HPP

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @enum ClientState
     * @brief A state representing a client
     */
    enum ClientState {
        CS_IN_LOBBY,
        CS_IN_ROOM,
        CS_IN_GAME
    };
}

#endif //R_TYPE_CLIENTSTATE_HPP
