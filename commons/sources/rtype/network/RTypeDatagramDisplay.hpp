/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagramDisplay.hpp
*/

/* Created the 18/11/2019 at 17:00 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAMDISPLAY_HPP
#define R_TYPE_RTYPEDATAGRAMDISPLAY_HPP

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
         * @struct RTypeDatagramDisplay
         * @brief A datagram display packet infos
         */
        struct RTypeDatagramDisplay {
            struct Vector2 {
                int x; /*!< x component */
                int y; /*!< y component */
            };
            struct Vector3 {
                int x; /*!< x component */
                int y; /*!< y component */
                int z; /*!< z component */
            };

            uint64_t entityId; /*!< Entity id */
            Vector3 position; /*!< position */
            Vector2 rotation; /*!< rotation */
            Vector2 scale; /*!< scale */
            uint32_t type; /*!< entity type */
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAMDISPLAY_HPP
