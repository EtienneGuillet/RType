/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** HostInfos.hpp
*/

/* Created the 24/09/2019 at 21:16 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_HOSTINFOS_HPP
#define B12NETWORKING_HOSTINFOS_HPP

#include <string>

/*!
 * @namespace b12software
 * @brief Main namespace for all b12 software
 */
namespace b12software {

    /*!
     * @namespace b12software::network
     * @brief Main namespace for networking stuff
     */
    namespace network {

        /*!
         * @struct HostInfos
         * @brief A structure holding host information
         */
        struct HostInfos {
            std::string host; /*!< The host as an address or a domain */
            unsigned short port; /*!< The port for this host */
            operator std::string() const {
                return host + ":" + std::to_string(port);
            };
        };

        const HostInfos emptyHost = {"", 0};
    }
}
#endif //B12NETWORKING_HOSTINFOS_HPP
