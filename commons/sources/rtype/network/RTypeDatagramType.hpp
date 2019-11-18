/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagramType.hpp
*/

/* Created the 18/11/2019 at 13:56 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAMTYPE_HPP
#define R_TYPE_RTYPEDATAGRAMTYPE_HPP
/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @namespace rtype::network
     * @brief A namespace that contains network related classes for the rtype project
     */
    namespace network {

        /*!
         * @enum RTypeDatagramType
         * @brief An enum with datagram op codes
         */
        enum RTypeDatagramType : unsigned short {
            T_100_CONNECT = 100,
            T_101_CONNECTED = 101,
            T_102_PING = 102,
            T_103_PONG = 103,
            T_104_DISCONNECT = 104,
            T_105_DISCONNECTED = 105,
            T_110_GET_ROOMS = 110,
            T_111_ROOM_LIST = 111,
            T_112_CREATE_ROOM = 112,
            T_113_ROOM_CREATED = 113,
            T_114_QUIT_ROOM = 114,
            T_115_ROOM_QUITTED = 115,
            T_116_JOIN_ROOM = 116,
            T_117_ROOM_JOINED = 117,
            T_200_ACTION = 200,
            T_210_DISPLAY = 210,
            T_220_LIVING = 220,
            T_230_CHARGE = 230,
            T_240_SCORE = 240,
            T_250_END_GAME = 250,
            T_260_GAME_ENDED = 260,
            T_300_UNKNOWN_PACKET = 300,
            T_301_INVALID_PACKET = 301,
            T_302_INVALID_PARAM = 302,
            T_303_USERNAME_ALREADY_USED = 303,
            T_304_ROOM_NAME_ALREADY_USED = 304,
            T_305_NOT_IN_A_ROOM = 305,
            T_306_UNKNOWN_ROOM = 306,
            T_307_INVALID_PASSWORD = 307,
            T_308_ROOM_FULL = 308,
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAMTYPE_HPP
