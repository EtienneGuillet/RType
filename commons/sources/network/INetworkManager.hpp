/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** INetworkManager.hpp
*/

/* Created the 25/09/2019 at 20:13 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_INETWORKMANAGER_HPP
#define B12NETWORKING_INETWORKMANAGER_HPP

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
            virtual udp::IUdpSocket *createNewUdpSocket() = 0;
            /*!
             * @brief Create a new ITcpClient
             * @return A ITcpClient
             */
            virtual tcp::ITcpClient *createNewTcpClient() = 0;
            /*!
             * @brief Create a new ITcpServer
             * @return A ITcpServer
             */
            virtual tcp::ITcpServer *createNewTcpServer() = 0;

            /*!
             * @brief Destroy a managed IUdpSocket
             * @param socket the socket to destroy
             */
            virtual void destroyUdpSocket(udp::IUdpSocket *socket) = 0;
            /*!
             * @brief Destroy a managed ITcpClient
             * @param client the client to destroy
             */
            virtual void destroyTcpClient(tcp::ITcpClient *client) = 0;
            /*!
             * @brief Destroy a managed ITcpServer
             * @param server the server to destroy
             */
            virtual void destroyTcpServer(tcp::ITcpServer *server) = 0;
        };
    }
}

#endif //B12NETWORKING_INETWORKMANAGER_HPP
