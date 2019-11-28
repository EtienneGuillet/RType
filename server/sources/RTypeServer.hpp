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
         * @param libsFolder The folder containing entities and systems libs
         */
        explicit RTypeServer(unsigned short port = 54321, std::string libsFolder = "./server");
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
        /*!
         * @brief Send looping datagrams to clients
         */
        void handleLooping();

    private:
        using ProtocolMapType = std::map<unsigned short, void (RTypeServer::*)(rtype::network::RTypeDatagram)>;
        static const ProtocolMapType protocolMap; /*!< A map used to handle incoming datagram*/

        static constexpr Client::Clock::duration lostConnectionDuration = std::chrono::milliseconds(2500);
        static constexpr Client::Clock::duration forceDisconnectDuration = std::chrono::milliseconds(5000);
        static constexpr Client::Clock::duration timeBetweenDatagramsDuration = std::chrono::milliseconds(500);

    private:
        /*!
         * @brief Get a client by his host
         * @param host the host to search for
         * @return The client with the host
         * @throw RTypeServerException if the client is not found
         */
        Client &getClientByHost(const b12software::network::HostInfos &host);
        /*!
         * @brief Get a client by his name
         * @param username the username to search for
         * @return The client with the username searched
         * @throw RTypeServerException if the client is not found
         */
        Client &getClientByUsername(const std::string &username);
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

        /*!
         * @brief Check if a given room name can be used
         * @param name the room name to check
         * @return 0 if it's valid, 1 if invalid name, 2 if name already taken
         */
        int isInvalidRoomName(const std::string &name);
        /*!
         * @brief Create a new room
         * @param name Name of the room
         * @param capacity capacity of the room
         * @param hasPassword does this room require a password
         * @param password the password of the room
         */
        void createRoom(const std::string &name, unsigned char capacity, bool hasPassword, const std::string &password);

        /*!
         * @brief Make a client join an existing room
         * @param roomName the name of the room to join
         * @param client The client that join this room
         * @param password The password to use to join this room
         */
        void joinRoom(const std::string &roomName, Client &client, const std::string &password = "");

        /*!
         * @brief Make a user exit the room he is in
         * @param client The client that exit his room
         */
        void exitRoom(Client &client);

        /*!
         * @brief Update room related infos
         */
        void handleRooms();

        /*!
         * @brief Update the rooms with a game running and start the ones who need it (room full)
         */
        void updateRooms();
        /*!
         * @brief Clean rooms with no user in it and no game running
         */
        void cleanRooms();

    private:
        /*!
         * @brief A handler called when a connect datagram is received
         * @param dg the received datagram
         */
        void protocol100ConnectDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a ping datagram is received
         * @param dg the received datagram
         */
        void protocol102PingDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a disconnect datagram is received
         * @param dg the received datagram
         */
        void protocol104DisconnectDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a client disconnected datagram is received
         * @param dg the received datagram
         */
        void protocol107ClientDisconnectedDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a new client connected datagram is received
         * @param dg the received datagram
         */
        void protocol109NewClientConnectedDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a get rooms datagram is received
         * @param dg the received datagram
         */
        void protocol110GetRoomsDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a create rooms datagram is received
         * @param dg the received datagram
         */
        void protocol112CreateRoomsDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a quit rooms datagram is received
         * @param dg the received datagram
         */
        void protocol114QuitRoomsDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a join rooms datagram is received
         * @param dg the received datagram
         */
        void protocol116JoinRoomsDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when an action datagram is received
         * @param dg the received datagram
         */
        void protocol200ActionDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a ok game ended datagram is received
         * @param dg the received datagram
         */
        void protocol260OkGameEndedDatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler called when a ok game started datagram is received
         * @param dg the received datagram
         */
        void protocol280OkGameStartedDatagramHandler(rtype::network::RTypeDatagram dg);
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
        std::list<std::shared_ptr<rtype::Room>> _rooms; /*!< Existing rooms */

        const std::string _libsFolder; /*< The path of the libraries folder */
    };
}

#endif //R_TYPE_RTYPESERVER_HPP
