/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioNetworkManager.hpp
*/

/* Created the 26/09/2019 at 11:19 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_ASIONETWORKMANAGER_HPP
#define B12NETWORKING_ASIONETWORKMANAGER_HPP

#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include "network/INetworkManager.hpp"

namespace b12software::network {

    /*!
     * @namespace b12software::asio
     * @brief Main namespace for networking with boost asio
     */
    namespace asio {

        /*!
         * @class AsioNetworkManager
         * @brief A network class that manage boost asio networking
         */
        class AsioNetworkManager : public b12software::network::INetworkManager {
        public:
            /*!
             * @brief ctor
             */
            AsioNetworkManager();
            /*!
             * @brief dtor
             */
            ~AsioNetworkManager() override;

            /*!
             * @brief cpy ctor
             */
            AsioNetworkManager(const AsioNetworkManager &other) = delete;

            /*!
             * @brief Assignment operator
             * @param rhs manager to assign to
             * @return *this
             */
            AsioNetworkManager &operator=(const AsioNetworkManager &rhs) = delete;

        public:
            void start() override;
            void stop() override;
            std::weak_ptr<udp::IUdpSocket> createNewUdpSocket() override;
            std::weak_ptr<tcp::ITcpClient> createNewTcpClient() override;
            std::weak_ptr<tcp::ITcpServer> createNewTcpServer() override;
            void destroyUdpSocket(const std::weak_ptr<udp::IUdpSocket> &socket) override;
            void destroyTcpClient(const std::weak_ptr<tcp::ITcpClient> &client) override;
            void destroyTcpServer(const std::weak_ptr<tcp::ITcpServer> &server) override;

        private:
            /*!
             * @brief Function exceuted on the network thread
             */
            static void networkingThreadFunc(AsioNetworkManager *manager);

        private:
            boost::asio::io_context _ioContext; /*!< Boost io context for this network manager */
            boost::asio::io_context::work *_worker; /*!< Boost object used such that _ioContext.run() does not terminate for lack of work */
            std::vector<std::shared_ptr<udp::IUdpSocket>> _udpSockets; /*!< Managed udp sockets */
            std::vector<std::shared_ptr<tcp::ITcpClient>> _tcpClients; /*!< Managed tcp clients */
            std::vector<std::shared_ptr<tcp::ITcpServer>> _tcpServers; /*!< Managed tcp servers */
            std::thread _networkThread; /*!< Network thread */
            bool _started; /*!< Is the network manager started */
        };
    }
}

#endif //B12NETWORKING_ASIONETWORKMANAGER_HPP
