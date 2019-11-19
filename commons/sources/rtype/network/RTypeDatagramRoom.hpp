/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagramRoom.hpp
*/

/* Created the 18/11/2019 at 16:49 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAMROOM_HPP
#define R_TYPE_RTYPEDATAGRAMROOM_HPP

#include <string>

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
         * @class RTypeDatagramRoom
         * @brief A room in a datagram
         */
        struct RTypeDatagramRoom {
            std::string name; /*!< Will be truncated if more than 10 chars */
            unsigned char capacity; /*!< The room maximal capacity */
            unsigned char slotUsed; /*!< The number of slots used */
            bool hasPassword; /*!< Does this room have a password */
            std::string password; /*!< A password */
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAMROOM_HPP
