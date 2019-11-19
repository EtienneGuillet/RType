/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagramAction.hpp
*/

/* Created the 18/11/2019 at 17:23 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAMACTION_HPP
#define R_TYPE_RTYPEDATAGRAMACTION_HPP

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
         * @struct RTypeDatagramAction
         * @brief A structure for a datagram action
         */
        struct RTypeDatagramAction {
            bool shot; /*!< Is the user pressing shot key */
            bool up; /*!< Is the user pressing up key */
            bool down; /*!< Is the user pressing down key */
            bool left; /*!< Is the user pressing left key */
            bool right; /*!< Is the user pressing right key */
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAMACTION_HPP
