/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagramLiving.hpp
*/

/* Created the 18/11/2019 at 17:33 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAMLIVING_HPP
#define R_TYPE_RTYPEDATAGRAMLIVING_HPP

#include <cstdint>

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
         * @struct RTypeDatagramLiving
         * @brief A living datagram data
         */
        struct RTypeDatagramLiving {
            uint64_t entityId; /*!< the entity id */
            int life; /*!< the entity life */
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAMLIVING_HPP
