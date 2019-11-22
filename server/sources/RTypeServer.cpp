/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeServer.cpp
*/

/* Created the 21/11/2019 at 17:59 by julian.frabel@epitech.eu */

#include <exception/NetworkException.hpp>
#include <logger/DefaultLogger.hpp>
#include "RTypeServer.hpp"
#include "network/asio/AsioNetworkManager.hpp"
#include "exception/RTypeServerException.hpp"

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
        auto dg = locketSocket->receive();

        std::string debugMessage = "Received datagram from " + dg.getHostInfos().host + ":" + std::to_string(dg.getHostInfos().port);
        debugMessage += " message (" + std::to_string(dg.getDatagramSize()) + " bytes) [" + std::string(reinterpret_cast<const char *>(dg.getData()), dg.getDatagramSize()) + "]";
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, debugMessage);
    }
}
