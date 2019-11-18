/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagram.hpp
*/

/* Created the 18/11/2019 at 13:11 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAM_HPP
#define R_TYPE_RTYPEDATAGRAM_HPP

#include "network/HostInfos.hpp"
#include "network/udp/Datagram.hpp"

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
         * @class RTypeDatagram
         * @brief A class that will implement the rfc 42069 about the rtype communication protocol
         */
        class RTypeDatagram : public b12software::network::udp::Datagram {
        public:
            using Datagram = b12software::network::udp::Datagram;
            using HostInfos = b12software::network::HostInfos;

        public:
            /*!
             * @brief ctor
             */
            RTypeDatagram();
            /*!
             * @brief cpy ctor
             * @param other The datagram to build from
             */
            RTypeDatagram(const RTypeDatagram &other);
            /*!
             * @brief build a RTypeDatagram from a b12 Datagram
             * @param other the datagram to build from
             */
            RTypeDatagram(const Datagram &other);
            /*!
             * @brief ctor
             * @param destination The destination to set this datagram to
             */
            explicit RTypeDatagram(const HostInfos &destination);
            /*!
             * @brief ctor
             * @param data The data to set this datagram to
             * @param size The size of the data
             */
            RTypeDatagram(const void *data, size_t size);
            /*!
             * @brief ctor
             * @param destination The destination to set this datagram to
             * @param data The data to set this datagram to
             * @param size The size of the data
             */
            RTypeDatagram(const HostInfos &destination, const void *data, size_t size);
            /*!
             * @brief dtor
             */
            ~RTypeDatagram() override;

            /*!
             * @brief Assign a rtype datagram to this datagram
             * @param rhs the datagram to assign
             * @return *this
             */
            RTypeDatagram &operator=(const RTypeDatagram &rhs);
            /*!
             * @brief Assign a b12 datagram to this datagram
             * @param rhs the datagram to assign
             * @return *this
             */
            RTypeDatagram &operator=(const Datagram &rhs) override;
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAM_HPP
