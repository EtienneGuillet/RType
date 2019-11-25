/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeServer.hpp
*/

/* Created the 21/11/2019 at 17:59 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPESERVER_HPP
#define R_TYPE_RTYPESERVER_HPP

#include <map>
#include "containers/ThreadSafeList.hpp"
#include "rtype/network/RTypeDatagramType.hpp"
#include "rtype/network/RTypeDatagram.hpp"
#include "network/INetworkManager.hpp"
#include "client/Client.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class RTypeServer
     * @brief A class that represent a RType server
     */
    class RTypeServer {
    public:
        /*!
         * @brief ctor
         * @param port The port of the server to use
         */
        explicit RTypeServer(unsigned short port = 54321);
        /*!
         * @brief dtor
         */
        ~RTypeServer();

        /*!
         * @brief Cpy ctor deleted
         * @param other server to create from
         */
        RTypeServer(const RTypeServer &other) = delete;

        /*!
         * @brief assignment operator deleted
         * @param rhs server to assign to
         * @return *this
         */
        RTypeServer &operator=(const RTypeServer &rhs) = delete;

    public:
        /*!
         * @brief Run a frame of the server
         */
        void run();

    private:
        /*!
         * @brief Handle incomming datagrams
         */
        void handleDatagrams();
        /*!
         * @brief Disconnect useless clients
         */
        void handleLiveness();

    private:
        using ProtocolMapType = std::map<unsigned short, void (RTypeServer::*)(rtype::network::RTypeDatagram)>;
        static const ProtocolMapType protocolMap; /*!< A map used to handle incoming datagram*/

        static constexpr Client::Clock::duration lostConnectionDuration = std::chrono::milliseconds(2500);
        static constexpr Client::Clock::duration forceDisconnectDuration = std::chrono::milliseconds(5000);
        static constexpr Client::Clock::duration timeBetweenDatagramsDuration = std::chrono::milliseconds(50);

    private:
        /*!
         * @brief Check if a given username can be used
         * @param username the username to check
         * @return 0 if it's valid, 1 if invalid username, 2 if username already taken
         */
        int isInvalidUsername(const std::string &username);

        /*!
         * @brief Add a new client to this server
         * @param client the client to add
         */
        void addNewClient(const Client &client);

        /*!
         * @brief Update the fact that the client is alive for this host
         * @param host The host of the alive client
         */
        void updateClientLiveness(const b12software::network::HostInfos &host);

        /*!
         * @brief Disconnect a client
         * @param client The client to disconnect
         */
        void disconnectClient(const Client &client);

    private:
        /*!
         * @brief A handler called when a ping datagram is received
         * @param dg the received datagram
         */
        void protocol102PingDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a connect datagram is received
         * @param dg the received datagram
         */
        void protocol100ConnectDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief Default handler called when an unknown datagram type comes in
         * @param dg the received datagram
         */
        void unknownDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief Send an invalid datagram to the client
         * @param dg the received datagram
         */
        void invalidDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that does nothing
         * @param dg the received datagram
         */
        void emptyDatagramHandler(rtype::network::RTypeDatagram dg);

    private:
        std::unique_ptr<b12software::network::INetworkManager> _networkManager; /*!< The network manager of this server */
        std::weak_ptr<b12software::network::udp::IUdpSocket> _socket; /*!< This server udp socket */

        b12software::containers::ThreadSafeList<rtype::Client> _clients; /*!< Connected clients */
    };
}

#endif //R_TYPE_RTYPESERVER_HPP
