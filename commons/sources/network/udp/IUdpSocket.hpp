/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** IUdpSocket.hpp
*/

/* Created the 24/09/2019 at 20:16 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_IUDPSOCKET_HPP
#define B12NETWORKING_IUDPSOCKET_HPP

#include "network/HostInfos.hpp"
#include "Datagram.hpp"

namespace b12software::network {

    /*!
     * @namespace b12software::network::udp
     * @brief UDP related classes namespace
     */
    namespace udp {

        /*!
         * @class IUdpSocket
         * @brief An interface describing the use cases of an UDP socket
         */
        class IUdpSocket {
        public:
            /*!
             * @brief dtor
             */
            virtual ~IUdpSocket() = default;

            /*!
             * @brief Bind this socket to a port
             * @param port The port to bind to
             */
            virtual void bind(unsigned short port) = 0;
            /*!
             * @brief Unbind this socket from the port it was bind to
             *
             * If the socket wasn't bind this function should do nothing
             */
            virtual void unbind() = 0;

            /*!
             * @brief Register a host to send the datagram to
             * @param infos The host to send datagram to
             */
            virtual void registerHost(const HostInfos &infos) = 0;
            /*!
             * @brief Remove the host to send to
             *
             * If no host was set this function should do nothing
             */
            virtual void unregisterHost() = 0;

            /*!
             * @brief Send raw data from this socket
             * @param data The data to send
             * @param size The size of this data
             * @param infos Information about the host that should receive the data
             *
             * This function should overwrite the infos parameter if an host was set
             */
            virtual void send(const void *data, size_t size, const HostInfos &infos) = 0;
            /*!
             * @brief Send a datagram
             * @param datagram The datagram to set
             *
             * This function should overwrite the datagram destination if an host was set
             */
            virtual void send(const Datagram &datagram) = 0;

            /*!
             * @brief Receive a datagram if there is one available
             * @return The datagram or an invalid datagram if none was available
             */
            virtual Datagram receive() = 0;

            /*!
             * @brief Get if there are datagram available for this socket
             * @return true if datagram are available false otherwise
             */
            virtual bool hasPendingDatagrams() const = 0;

            /*!
             * @brief Get the bind port
             * @return 0 if no port has been bind or the port
             */
            virtual unsigned short getPort() const = 0;

            /*!
             * @brief Get the address of this socket
             * @return the address of this socket
             */
            virtual std::string getAddress() const = 0;
        };
    }
}

#endif //B12NETWORKING_IUDPSOCKET_HPP
