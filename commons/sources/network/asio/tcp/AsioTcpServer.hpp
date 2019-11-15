/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioTcpServer.hpp
*/

/* Created the 26/09/2019 at 11:37 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_ASIOTCPSERVER_HPP
#define B12NETWORKING_ASIOTCPSERVER_HPP

#include <map>
#include <vector>
#include <queue>
#include <mutex>
#include <boost/asio.hpp>
#include "network/tcp/ITcpServer.hpp"
#include "AsioTcpClient.hpp"

namespace b12software::network {

    /*!
     * @namespace b12software::asio
     * @brief Main namespace for networking with boost asio
     */
    namespace asio {

        /*!
         * @class AsioTcpServer
         * @brief Boost asio implementation of a tcp server
         */
        class AsioTcpServer : public b12software::network::tcp::ITcpServer {
        private:
            using acceptor = boost::asio::ip::tcp::acceptor;
            using endpoint = boost::asio::ip::tcp::endpoint;
            using mutex = std::recursive_mutex;
            using lock = std::scoped_lock<mutex>;

        public:
            /*!
             * @brief ctor
             * @param context boost io context
             */
            AsioTcpServer(boost::asio::io_context &context);
            /*!
             * @brief dtor
             */
            ~AsioTcpServer() override;

        public:
            void bind(int port) override;
            void unbind() override;
            void disconnect(int clientId) override;
            void sendToAll(const void *data, size_t size) override;
            void sendToAll(const tcp::IPacket &packet) override;
            void sendToClient(int clientId, const void *data, size_t size) override;
            void sendToClient(int clientId, const tcp::IPacket &packet) override;
            void sendToClients(const std::vector<int> &clientIds, const void *data, size_t size) override;
            void sendToClients(const std::vector<int> &clientIds, const tcp::IPacket &packet) override;
            void sendExceptClients(const std::vector<int> &exceptIds, const void *data, size_t size) override;
            void sendExceptClients(const std::vector<int> &exceptIds, const tcp::IPacket &packet) override;
            std::vector<int> getConnectedClientIds() override;
            std::vector<int> getNewConnectedClientIds() override;
            std::vector<int> getDisconnectedClientIds() override;
            std::weak_ptr<tcp::ITcpClient> getClientById(int clientId) override;

        private:
            /*!
             * @brief Compute disconnected clients
             */
            void recomputeDisconnected();
            /*!
             * @brief Start an async call to accept clients
             */
            void startAccept();

            /*!
             * @brief Handle a connection of a new client
             * @param client The new connected client to recompute data for
             * @param error Boost errors that could have happened
             */
            void handleAccept(boost::shared_ptr<AsioTcpClient> client, const boost::system::error_code& error);

        private:
            boost::asio::io_context &_context; /*!< The boost asio io context */
            acceptor _acceptor; /*!< The tcp acceptor of this server */
            std::map<int, std::shared_ptr<AsioTcpClient>> _clients; /*!< The connected clients stored with there ids */
            mutex _clientMapMutex; /*!< A mutex locking the client map*/
            mutex _idVectorMutex; /*!< A mutex locking the ids vector */
            std::vector<int> _newIds; /*!< A list of newly connected ids */
            std::queue<int> _freeIds; /*!< A list of available ids */
            std::vector<int> _disconnectedIds; /*!< A list of newly disconnected ids */
            int _maxId; /*!< The biggest id in use */
        };
    }
}

#endif //B12NETWORKING_ASIOTCPSERVER_HPP
