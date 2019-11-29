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
#include "NetworkState.hpp"
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
            NS_NONE,
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
        static constexpr std::chrono::milliseconds processDatagramsMaxTime = std::chrono::milliseconds(10); /*!< Allowed time to process datagrams per update */
        static constexpr long lobbyDatagramRetrySyncRate = 500; /*!< In ms */
        static constexpr long gameDatagramSyncRate = 100; /*!< In ms */
        static constexpr long serverConnectivityPingThreshHold = 2500; /*!< In ms */
        static constexpr long serverConnectionLostThreshHold = 5000; /*!< In ms */

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
         */
        void sendDatagrams(long deltatime);
        /*!
         * @brief Connection sequence
         */
        void connectionSequence();

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
