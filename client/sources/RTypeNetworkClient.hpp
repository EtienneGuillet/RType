/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeNetworkClient.hpp
*/

/* Created the 29/11/2019 at 17:37 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPENETWORKCLIENT_HPP
#define R_TYPE_RTYPENETWORKCLIENT_HPP

#include <map>
#include <memory>
#include "rtype/network/RTypeDatagramType.hpp"
#include "rtype/network/RTypeDatagram.hpp"
#include "rtype/client/NetworkState.hpp"
#include "network/INetworkManager.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class RTypeNetworkClient
     * @brief A class where all network calls are made
     */
    class RTypeNetworkClient {
    private:
        /*!
         * @enum NetworkSequence
         * @brief The sequence to run
         */
        enum NetworkSequence {
            NS_CONNECT,
            NS_LOBBY,
            NS_GAME,
            NS_LOST_CONNECTION
        };

    public:
        RTypeNetworkClient(NetworkState &syncTo);
        ~RTypeNetworkClient();
        RTypeNetworkClient(const RTypeNetworkClient &other) = delete;
        RTypeNetworkClient &operator=(const RTypeNetworkClient &rhs) = delete;

    public:
        /*!
         * @brief Update the network informations
         * @param deltatime the elapsed time since last update
         */
        void update(long deltatime);

    private:
        using ProtocolMapType = std::map<unsigned short, void (RTypeNetworkClient::*)(rtype::network::RTypeDatagram)>;
        static const ProtocolMapType protocolMap; /*!< A map used to handle incoming datagram */

        static constexpr std::chrono::milliseconds processDatagramsMaxTime = std::chrono::milliseconds(10); /*!< Allowed time to process datagrams per update */
        static constexpr long lobbyDatagramRetrySyncRate = 500; /*!< In ms */
        static constexpr long gameDatagramSyncRate = 10; /*!< In ms */
        static constexpr long serverConnectivityPingThreshHold = 2500; /*!< In ms */
        static constexpr long serverConnectionLostThreshHold = 5000; /*!< In ms */
        static constexpr long entityInvalidateDisplayAfter = 50; /*!< In ms */
        static constexpr long entityInvalidateEntityAfter = 100; /*!< In ms */

    private:
        void resetDatagram(rtype::network::RTypeDatagramType type);

    private:
        /*!
         * @brief Receive datagrams from server and update infos
         */
        void receiveDatagrams();
        /*!
         * @brief Process a datagram
         * @param dg the datagram to process
         */
        void processDatagram(rtype::network::RTypeDatagram &dg);
        /*!
         * @brief Sync datagram send in _datagrams
         * @param deltatime the elapsed time since last update
         */
        void sendDatagrams(long deltatime);
        /*!
         * @brief Connection sequence
         * @param deltatime the elapsed time since last update
         */
        void connectionSequence(long deltatime);
        /*!
         * @brief Lobby sequence
         * @param deltatime the elapsed time since last update
         */
        void lobbySequence(long deltatime);
        /*!
         * @brief Game sequence
         * @param deltatime the elapsed time since last update
         */
        void gameSequence(long deltatime);
        /*!
         * @brief Lost connection sequence
         * @param deltatime the elapsed time since last update
         */
        void lostConnectionSequence(long deltatime);

        /*!
         * @brief check if the client lost connection to server
         */
        void checkLostConnection();

        /*!
         * @brief Invalidate entities that have not been updated since a long time
         * @param deltatime elapsed time
         */
        void invalidateEntities(long deltatime);

    private:
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
        /*!
         * @brief Default handler called when an unknown datagram type comes in
         * @param dg the received datagram
         * This function should be removed by the correct handler
         */
        void nyiDatagramHandler(rtype::network::RTypeDatagram dg);

    private:
        /*!
         * @brief A handler that handle the 101 datagram
         * @param dg the received datagram
         */
        void connected101DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 102 datagram
         * @param dg the received datagram
         */
        void ping102DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 105 datagram
         * @param dg the received datagram
         */
        void disconnected105DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 106 datagram
         * @param dg the received datagram
         */
        void clientDisconnected106DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 108 datagram
         * @param dg the received datagram
         */
        void clientConnected108DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 111 datagram
         * @param dg the received datagram
         */
        void roomList111DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 113 datagram
         * @param dg the received datagram
         */
        void roomCreated113DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 115 datagram
         * @param dg the received datagram
         */
        void roomQuitted115DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 117 datagram
         * @param dg the received datagram
         */
        void roomJoined117DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 210 datagram
         * @param dg the received datagram
         */
        void display210DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 220 datagram
         * @param dg the received datagram
         */
        void living220DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 230 datagram
         * @param dg the received datagram
         */
        void charge230DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 240 datagram
         * @param dg the received datagram
         */
        void score240DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 250 datagram
         * @param dg the received datagram
         */
        void endGame250DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief A handler that handle the 270 datagram
         * @param dg the received datagram
         */
        void startGame270DatagramHandler(rtype::network::RTypeDatagram dg);

        /*!
         * @brief Handle the 303 error datagram
         * @param dg the received datagram
         */
        void error303DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief Handle the 304 error datagram
         * @param dg the received datagram
         */
        void error304DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief Handle the 306 error datagram
         * @param dg the received datagram
         */
        void error306DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief Handle the 307 error datagram
         * @param dg the received datagram
         */
        void error307DatagramHandler(rtype::network::RTypeDatagram dg);
        /*!
         * @brief Handle the 308 error datagram
         * @param dg the received datagram
         */
        void error308DatagramHandler(rtype::network::RTypeDatagram dg);

    private:
        std::unique_ptr<b12software::network::INetworkManager> _nm;
        std::weak_ptr<b12software::network::udp::IUdpSocket> _socket;
        NetworkState &_syncTo;
        std::map<rtype::network::RTypeDatagramType, std::pair<long, rtype::network::RTypeDatagram>> _datagrams;
        NetworkSequence _sequence;
        long _timeSinceLastServerReach;
    };
}
#endif //R_TYPE_RTYPENETWORKCLIENT_HPP
