/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeNetworkClient.cpp
*/

/* Created the 29/11/2019 at 17:37 by julian.frabel@epitech.eu */

#include "rtype/exceptions/DatagramMalformedException.hpp"
#include "logger/DefaultLogger.hpp"
#include "network/asio/AsioNetworkManager.hpp"
#include "RTypeNetworkClient.hpp"

const rtype::RTypeNetworkClient::ProtocolMapType rtype::RTypeNetworkClient::protocolMap = {
    {rtype::network::T_100_CONNECT, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_101_CONNECTED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_102_PING, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_103_PONG, &rtype::RTypeNetworkClient::emptyDatagramHandler},
    {rtype::network::T_104_DISCONNECT, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_105_DISCONNECTED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_106_CLIENT_DISCONNECTED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_107_OK_CLIENT_DISCONNECTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_108_NEW_CLIENT_CONNECTED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_109_OK_NEW_CLIENT_CONNECTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_110_GET_ROOMS, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_111_ROOM_LIST, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_112_CREATE_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_113_ROOM_CREATED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_114_QUIT_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_115_ROOM_QUITTED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_116_JOIN_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_117_ROOM_JOINED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_200_ACTION, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_210_DISPLAY, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_220_LIVING, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_230_CHARGE, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_240_SCORE, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_250_END_GAME, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_260_GAME_ENDED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_270_GAME_STARTING, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_280_GAME_STARTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_301_INVALID_PACKET, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_302_INVALID_PARAM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_303_USERNAME_ALREADY_USED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_304_ROOM_NAME_ALREADY_USED, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_305_NOT_IN_A_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_306_UNKNOWN_ROOM, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_307_INVALID_PASSWORD, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_308_ROOM_FULL, &rtype::RTypeNetworkClient::nyiDatagramHandler},
    {rtype::network::T_309_OPERATION_NOT_PERMITTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
};

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
    receiveDatagrams();
    checkLostConnection();
    switch (_sequence) {
    case NS_CONNECT: connectionSequence(deltatime);
        break;
    case NS_LOBBY: lobbySequence(deltatime);
        break;
    case NS_GAME: gameSequence(deltatime);
        break;
    case NS_LOST_CONNECTION: lostConnectionSequence(deltatime);
        break;
    default:
        break;
    }
    sendDatagrams(deltatime);
}

void rtype::RTypeNetworkClient::resetDatagram(rtype::network::RTypeDatagramType type)
{
    _datagrams[type].first = 0;
    _datagrams[type].second = rtype::network::RTypeDatagram();
}

void rtype::RTypeNetworkClient::receiveDatagrams()
{
    if (_sequence == NS_LOST_CONNECTION)
        return;
    auto lockedSocket = _socket.lock();
    if (!lockedSocket)
        return;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point curr = start;
    while (curr - start < processDatagramsMaxTime && lockedSocket->hasPendingDatagrams()) {
        rtype::network::RTypeDatagram dg = lockedSocket->receive();
        processDatagram(dg);
    }
}

void rtype::RTypeNetworkClient::processDatagram(rtype::network::RTypeDatagram &dg)
{
    auto it = protocolMap.find(dg.getType());
    if (it != protocolMap.end()) {
        try {
            (this->*(it->second))(dg);
            _timeSinceLastServerReach = 0;
        } catch (exceptions::DatagramMalformedException &e) {
            invalidDatagramHandler(dg);
        }
    } else {
        unknownDatagramHandler(dg);
    }
}

void rtype::RTypeNetworkClient::sendDatagrams(long deltatime)
{
    if (_sequence == NS_LOST_CONNECTION)
        return;
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

void rtype::RTypeNetworkClient::connectionSequence(long deltatime)
{
    if (!_syncTo.isConnnected() && _syncTo.isTryingToConnected()) {
        auto it = _datagrams.find(rtype::network::T_100_CONNECT);
        if (it == _datagrams.end() ||
            !_datagrams[rtype::network::T_100_CONNECT].second.isValid()) {
            rtype::network::RTypeDatagram dg({_syncTo.getServerHost(), _syncTo.getServerPort()});
            dg.init100ConnectDatagram(_syncTo.getLobbyState().getUsername());
            _datagrams[rtype::network::T_100_CONNECT].first = 0;
            _datagrams[rtype::network::T_100_CONNECT].second = dg;
        } else if (_timeSinceLastServerReach > serverConnectivityPingThreshHold - 100) {
            _syncTo.setConnectionStatus(false, "Could not reach server");
        }
        _timeSinceLastServerReach += deltatime;
    } else if (_syncTo.isConnnected()) {
        _sequence = NS_LOBBY;
        _timeSinceLastServerReach += deltatime;
    }
}

void rtype::RTypeNetworkClient::lobbySequence(long deltatime)
{
    auto &lobbyState = _syncTo.getLobbyState();
    rtype::network::RTypeDatagram dg({_syncTo.getServerHost(), _syncTo.getServerPort()});
    //get lobby
    if (lobbyState.isUpdatingLobby()) {
        if (_datagrams.find(rtype::network::T_110_GET_ROOMS) == _datagrams.end() || !_datagrams[rtype::network::T_110_GET_ROOMS].second.isValid()) {
            _datagrams[rtype::network::T_110_GET_ROOMS].first = lobbyDatagramRetrySyncRate;
            dg.initSingleOpCodeDatagram(rtype::network::T_110_GET_ROOMS);
            _datagrams[rtype::network::T_110_GET_ROOMS].second = dg;
        }
    }
    //create lobby
    if (lobbyState.isCreatingLobby()) {
        if (_datagrams.find(rtype::network::T_112_CREATE_ROOM) == _datagrams.end() || !_datagrams[rtype::network::T_112_CREATE_ROOM].second.isValid()) {
            _datagrams[rtype::network::T_112_CREATE_ROOM].first = lobbyDatagramRetrySyncRate;
            rtype::network::RTypeDatagramRoom room;
            room.name = lobbyState.getCurrentLobbyData().name;
            room.hasPassword = lobbyState.getCurrentLobbyData().hasPassword;
            room.password = lobbyState.getCurrentLobbyData().password;
            room.capacity = lobbyState.getCurrentLobbyData().size;
            room.slotUsed = lobbyState.getCurrentLobbyData().nbPlayers;
            dg.init112CreateRoomDatagram(room);
            _datagrams[rtype::network::T_112_CREATE_ROOM].second = dg;
        }
    }
    //join lobby
    if (lobbyState.isJoiningLobby()) {
        if (_datagrams.find(rtype::network::T_116_JOIN_ROOM) == _datagrams.end() || !_datagrams[rtype::network::T_116_JOIN_ROOM].second.isValid()) {
            _datagrams[rtype::network::T_116_JOIN_ROOM].first = lobbyDatagramRetrySyncRate;
            rtype::network::RTypeDatagramRoom room;
            room.name = lobbyState.getCurrentLobbyData().name;
            room.hasPassword = lobbyState.getCurrentLobbyData().hasPassword;
            room.password = lobbyState.getCurrentLobbyData().password;
            room.capacity = lobbyState.getCurrentLobbyData().size;
            room.slotUsed = lobbyState.getCurrentLobbyData().nbPlayers;
            dg.init116JoinRoomDatagram(room);
            _datagrams[rtype::network::T_116_JOIN_ROOM].second = dg;
        }
    }
    //quit lobby
    if (lobbyState.isQuittingLobby()) {
        if (_datagrams.find(rtype::network::T_114_QUIT_ROOM) == _datagrams.end() || !_datagrams[rtype::network::T_114_QUIT_ROOM].second.isValid()) {
            _datagrams[rtype::network::T_114_QUIT_ROOM].first = lobbyDatagramRetrySyncRate;
            dg.initSingleOpCodeDatagram(rtype::network::T_114_QUIT_ROOM);
            _datagrams[rtype::network::T_114_QUIT_ROOM].second = dg;
        }
    }
    _timeSinceLastServerReach += deltatime;
}

void rtype::RTypeNetworkClient::gameSequence(long deltatime)
{
    auto inputs = _syncTo.getInputs();
    auto it = _datagrams.find(rtype::network::T_200_ACTION);
    if (it == _datagrams.end() ||
        !_datagrams[rtype::network::T_200_ACTION].second.isValid()) {
        _datagrams[rtype::network::T_200_ACTION].first = gameDatagramSyncRate;
    }
    rtype::network::RTypeDatagram dg({_syncTo.getServerHost(), _syncTo.getServerPort()});
    rtype::network::RTypeDatagramAction actions;
    actions.shot = inputs[SPACE];
    actions.up = inputs[Z];
    actions.down = inputs[S];
    actions.left = inputs[Q];
    actions.right = inputs[D];
    dg.init200ActionDatagram(actions);
    _datagrams[rtype::network::T_200_ACTION].second = dg;
    _timeSinceLastServerReach += deltatime;
}

void rtype::RTypeNetworkClient::lostConnectionSequence([[maybe_unused]]long deltatime)
{}

void rtype::RTypeNetworkClient::checkLostConnection()
{
    if (_sequence == NS_LOST_CONNECTION)
        return;
    if (_timeSinceLastServerReach >= serverConnectivityPingThreshHold && _timeSinceLastServerReach < serverConnectionLostThreshHold) {
        rtype::network::RTypeDatagram dg({_syncTo.getServerHost(), _syncTo.getServerPort()});
        dg.initSingleOpCodeDatagram(rtype::network::T_102_PING);
        _datagrams[rtype::network::T_102_PING].first = lobbyDatagramRetrySyncRate;
        _datagrams[rtype::network::T_102_PING].second = dg;
    } else if (_timeSinceLastServerReach >= serverConnectionLostThreshHold) {
        _sequence = NS_LOST_CONNECTION;
    }
}

void rtype::RTypeNetworkClient::unknownDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_300_UNKNOWN_PACKET);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "] Unknown opcode received: " + std::to_string(dg.getType()));
    _socket.lock()->send(response);
}

void rtype::RTypeNetworkClient::invalidDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_301_INVALID_PACKET);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "] Valid opcode (" + std::to_string(dg.getType()) + ") received but was malformed or not expected");
    _socket.lock()->send(response);
}

void rtype::RTypeNetworkClient::emptyDatagramHandler(rtype::network::RTypeDatagram dg)
{
    resetDatagram(rtype::network::T_102_PING);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][" + std::to_string(dg.getType()) + "] Empty handler");
}

void rtype::RTypeNetworkClient::nyiDatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_300_UNKNOWN_PACKET);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "] NYI OpCode: " + std::to_string(dg.getType()));
    _socket.lock()->send(response);
}
