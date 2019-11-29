/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeNetworkClient.cpp
*/

/* Created the 29/11/2019 at 17:37 by julian.frabel@epitech.eu */

#include "network/asio/AsioNetworkManager.hpp"
#include "RTypeNetworkClient.hpp"

rtype::RTypeNetworkClient::RTypeNetworkClient(rtype::NetworkState &syncTo)
    : _nm()
    , _socket()
    , _syncTo(syncTo)
    , _datagrams()
    , _sequence(NS_CONNECT)
    , _timeSinceLastServerReach(0)
{
    _nm = std::make_unique<b12software::network::asio::AsioNetworkManager>();
    _nm->start();
    _socket = _nm->createNewUdpSocket();
    _socket.lock()->bind(0);
}

rtype::RTypeNetworkClient::~RTypeNetworkClient()
{
    _nm->stop();
}

void rtype::RTypeNetworkClient::update(long deltatime)
{
    switch (_sequence) {
    case NS_CONNECT: connectionSequence();
        break;
    case NS_LOBBY:
        break;
    case NS_GAME:
        break;
    case NS_LOST_CONNECTION:
        break;
    default:
        break;
    }
    sendDatagrams(deltatime);
}

void rtype::RTypeNetworkClient::receiveDatagrams()
{
    auto lockedSocket = _socket.lock();
    if (!lockedSocket)
        return;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point curr = start;
    while (curr - start < processDatagramsMaxTime && lockedSocket->hasPendingDatagrams()) {
        rtype::network::RTypeDatagram dg = lockedSocket->receive();
    }
}

void rtype::RTypeNetworkClient::processDatagram(rtype::network::RTypeDatagram &dg)
{

}

void rtype::RTypeNetworkClient::sendDatagrams(long deltatime)
{
    auto lockedSocket = _socket.lock();
    if (!lockedSocket)
        return;
    for (auto & pair : _datagrams) {
        auto datagramOpCode = pair.first;
        auto &datagramDelta = pair.second.first;
        auto &datagram = pair.second.second;
        if (!datagram.isValid())
            continue;
        datagramDelta += deltatime;
        if (datagramOpCode < 200 && datagramDelta >= lobbyDatagramRetrySyncRate) {
            lockedSocket->send(datagram);
            datagramDelta -= lobbyDatagramRetrySyncRate;
        } else if (datagramOpCode >= 200 && datagramDelta >= gameDatagramSyncRate) {
            lockedSocket->send(datagram);
            datagramDelta -= gameDatagramSyncRate;
        }
    }
}

void rtype::RTypeNetworkClient::connectionSequence()
{

}
