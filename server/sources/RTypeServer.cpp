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
#include "rtype/exceptions/DatagramMalformedException.hpp"

const rtype::RTypeServer::ProtocolMapType rtype::RTypeServer::protocolMap = {
    {rtype::network::T_100_CONNECT, &rtype::RTypeServer::protocol100ConnectDatagramHandler},
    {rtype::network::T_101_CONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_102_PING, &rtype::RTypeServer::protocol102PingDatagramHandler},
    {rtype::network::T_103_PONG, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_104_DISCONNECT, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_105_DISCONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_106_CLIENT_DISCONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_107_OK_CLIENT_DISCONNECTED, &rtype::RTypeServer::invalidDatagramHandler}, // todo
    {rtype::network::T_108_NEW_CLIENT_CONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_109_OK_NEW_CLIENT_CONNECTED, &rtype::RTypeServer::invalidDatagramHandler}, // todo
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
    {rtype::network::T_309_OPERATION_NOT_PERMITTED, &rtype::RTypeServer::invalidDatagramHandler},
};

rtype::RTypeServer::RTypeServer(unsigned short port)
    : _networkManager(std::make_unique<b12software::network::asio::AsioNetworkManager>()),
      _socket(),
      _clients()
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
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "[RTYPESERVER] RType server listening on " + lockedSocket->getAddress() + ":" + std::to_string(lockedSocket->getPort()));
}

rtype::RTypeServer::~RTypeServer()
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelInfo, "[RTYPESERVER] RType server closing");
}

void rtype::RTypeServer::run()
{
    auto locketSocket = _socket.lock();
    if (locketSocket->hasPendingDatagrams()) {
        rtype::network::RTypeDatagram dg = locketSocket->receive();
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER] Received datagram from " + static_cast<std::string>(dg.getHostInfos()) + "(" + std::to_string(dg.getDatagramSize()) + " bytes)(code: " + std::to_string(dg.getType()) + ")");
        auto it = protocolMap.find(dg.getType());
        if (it != protocolMap.end()) {
            try {
                (this->*(it->second))(dg);
            } catch (exceptions::DatagramMalformedException &e) {
                invalidDatagramHandler(dg);
            }
        } else {
            unknownDatagramHandler(dg);
        }
    }
}

int rtype::RTypeServer::isInvalidUsername(const std::string &username)
{
    if (username.empty())
        return 1;
    std::scoped_lock lock(_clients);
    for (auto &client : _clients) {
        if (client.getUsername() == username)
            return 2;
    }
    return 0;
}

void rtype::RTypeServer::unknownDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_300_UNKNOWN_PACKET);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "] Unknown opcode received: " + std::to_string(dg.getType()));
    _socket.lock()->send(response);
}

void rtype::RTypeServer::invalidDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_301_INVALID_PACKET);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "] Valid opcode (" + std::to_string(dg.getType()) + ") received but was malformed or not expected");
    _socket.lock()->send(response);
}

void rtype::RTypeServer::protocol102PingDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_103_PONG);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][102] Sending 103 pong");
    _socket.lock()->send(response);
}

void rtype::RTypeServer::protocol100ConnectDatagramHandler(rtype::network::RTypeDatagram dg)
{
    std::string username;
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    dg.extract100ConnectDatagram(username);
    int invalidUsernameCode = isInvalidUsername(username);
    switch (invalidUsernameCode) {
    case 1:
        response.initSingleOpCodeDatagram(rtype::network::T_302_INVALID_PARAM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] Invalid username '" + username + "'");
        break;
    case 2:
        response.initSingleOpCodeDatagram(rtype::network::T_303_USERNAME_ALREADY_USED);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] Already used username '" + username + "'");
        break;
    default:
        response.initSingleOpCodeDatagram(rtype::network::T_101_CONNECTED);
        _clients.push_back(Client(dg.getHostInfos(), username));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] A new client connected with username '" + username + "'");
        break;
    }
    _socket.lock()->send(response);
}