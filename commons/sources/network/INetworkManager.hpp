/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** INetworkManager.hpp
*/

/* Created the 25/09/2019 at 20:13 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_INETWORKMANAGER_HPP
#define B12NETWORKING_INETWORKMANAGER_HPP

#include <memory>
#include "network/udp/IUdpSocket.hpp"
#include "network/tcp/ITcpClient.hpp"
#include "network/tcp/ITcpServer.hpp"

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
         * @class INetworkManager
         * @brief An interface describing the network manager
         */
        class INetworkManager {
        public:
            /*!
             * @brief dtor
             */
            virtual ~INetworkManager() = default;

            /*!
             * @brief Start this network manager, network manager should start processing network io
             */
            virtual void start() = 0;

            /*!
             * @brief Stop this network manager, network manager should stop processing network io
             */
            virtual void stop() = 0;

            /*!
             * @brief Create a new IUdpSocket
             * @return A IUdpSocket
             */
            virtual std::weak_ptr<udp::IUdpSocket> createNewUdpSocket() = 0;
            /*!
             * @brief Create a new ITcpClient
             * @return A ITcpClient
             */
            virtual std::weak_ptr<tcp::ITcpClient> createNewTcpClient() = 0;
            /*!
             * @brief Create a new ITcpServer
             * @return A ITcpServer
             */
            virtual std::weak_ptr<tcp::ITcpServer> createNewTcpServer() = 0;

            /*!
             * @brief Indicate to the manager that this socket is not needed anymore
             * @param socket the socket not needed
             */
            virtual void destroyUdpSocket(const std::weak_ptr<udp::IUdpSocket> &socket) = 0;
            /*!
             * @brief Indicate to the manager that this client is not needed anymore
             * @param client the client not needed
             */
            virtual void destroyTcpClient(const std::weak_ptr<tcp::ITcpClient> &client) = 0;
            /*!
             * @brief Indicate to the manager that this server is not needed anymore
             * @param server the server not needed
             */
            virtual void destroyTcpServer(const std::weak_ptr<tcp::ITcpServer> &server) = 0;
        };
    }
}

#endif //B12NETWORKING_INETWORKMANAGER_HPP
