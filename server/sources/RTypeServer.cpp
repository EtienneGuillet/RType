/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeServer.cpp
*/

/* Created the 21/11/2019 at 17:59 by julian.frabel@epitech.eu */

#include "RTypeServer.hpp"
#include "exception/NetworkException.hpp"
#include "logger/DefaultLogger.hpp"
#include "network/asio/AsioNetworkManager.hpp"
#include "exception/RTypeServerException.hpp"

const rtype::RTypeServer::ProtocolMapType rtype::RTypeServer::protocolMap = {
    {rtype::network::T_102_PING, &rtype::RTypeServer::protocol102PingDatagramHandler}
};

rtype::RTypeServer::RTypeServer(unsigned short port)
    : _networkManager(std::make_unique<b12software::network::asio::AsioNetworkManager>()),
      _socket()
{
    if (!_networkManager)
        throw rtype::exception::RTypeServerException("Failed to initialize network manager", WHERE);
    _networkManager->start();
    _socket = _networkManager->createNewUdpSocket();
    auto lockedSocket = _socket.lock();
    if (!lockedSocket)
        throw rtype::exception::RTypeServerException("Failed to create server socket", WHERE);
    try {
        lockedSocket->bind(port);
    } catch (b12software::exception::NetworkException &e) {
        throw rtype::exception::RTypeServerException(e.what(), WHERE + std::string(" coming from ") + e.where());
    }
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "RType server listening on " + lockedSocket->getAddress() + ":" + std::to_string(lockedSocket->getPort()));
}

rtype::RTypeServer::~RTypeServer()
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "RType server closing");
}

void rtype::RTypeServer::run()
{
    auto locketSocket = _socket.lock();
    if (locketSocket->hasPendingDatagrams()) {
        rtype::network::RTypeDatagram dg = locketSocket->receive();
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Received datagram from " + dg.getHostInfos().host + ":" + std::to_string(dg.getHostInfos().port) + "(" + std::to_string(dg.getDatagramSize()) + " bytes)");
        auto it = protocolMap.find(dg.getType());
        if (it != protocolMap.end()) {
            (this->*(it->second))(dg);
        } else {
            unknownDatagramHandler(dg);
        }
    }
}

void rtype::RTypeServer::protocol102PingDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_103_PONG);
    _socket.lock()->send(response);
}

void rtype::RTypeServer::unknownDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_300_UNKNOWN_PACKET);
    _socket.lock()->send(response);
}
