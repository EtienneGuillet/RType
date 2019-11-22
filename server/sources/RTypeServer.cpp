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
    {rtype::network::T_100_CONNECT, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_101_CONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_102_PING, &rtype::RTypeServer::protocol102PingDatagramHandler},
    {rtype::network::T_103_PONG, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_104_DISCONNECT, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_105_DISCONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_110_GET_ROOMS, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_111_ROOM_LIST, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_112_CREATE_ROOM, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_113_ROOM_CREATED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_114_QUIT_ROOM, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_115_ROOM_QUITTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_116_JOIN_ROOM, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_117_ROOM_JOINED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_200_ACTION, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_210_DISPLAY, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_220_LIVING, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_230_CHARGE, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_240_SCORE, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_250_END_GAME, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_260_GAME_ENDED, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_300_UNKNOWN_PACKET, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_301_INVALID_PACKET, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_302_INVALID_PARAM, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_303_USERNAME_ALREADY_USED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_304_ROOM_NAME_ALREADY_USED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_305_NOT_IN_A_ROOM, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_306_UNKNOWN_ROOM, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_307_INVALID_PASSWORD, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_308_ROOM_FULL, &rtype::RTypeServer::invalidDatagramHandler},
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

void rtype::RTypeServer::invalidDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_301_INVALID_PACKET);
    _socket.lock()->send(response);
}
