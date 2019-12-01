/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeNetworkClient.cpp
*/

/* Created the 29/11/2019 at 17:37 by julian.frabel@epitech.eu */

#include "exception/GameStateException.hpp"
#include "rtype/exceptions/DatagramMalformedException.hpp"
#include "logger/DefaultLogger.hpp"
#include "network/asio/AsioNetworkManager.hpp"
#include "RTypeNetworkClient.hpp"

const rtype::RTypeNetworkClient::ProtocolMapType rtype::RTypeNetworkClient::protocolMap = {
    {rtype::network::T_100_CONNECT, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_101_CONNECTED, &rtype::RTypeNetworkClient::connected101DatagramHandler},
    {rtype::network::T_102_PING, &rtype::RTypeNetworkClient::ping102DatagramHandler},
    {rtype::network::T_103_PONG, &rtype::RTypeNetworkClient::emptyDatagramHandler},
    {rtype::network::T_104_DISCONNECT, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_105_DISCONNECTED, &rtype::RTypeNetworkClient::disconnected105DatagramHandler},
    {rtype::network::T_106_CLIENT_DISCONNECTED, &rtype::RTypeNetworkClient::clientDisconnected106DatagramHandler},
    {rtype::network::T_107_OK_CLIENT_DISCONNECTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_108_NEW_CLIENT_CONNECTED, &rtype::RTypeNetworkClient::clientConnected108DatagramHandler},
    {rtype::network::T_109_OK_NEW_CLIENT_CONNECTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_110_GET_ROOMS, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_111_ROOM_LIST, &rtype::RTypeNetworkClient::roomList111DatagramHandler},
    {rtype::network::T_112_CREATE_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_113_ROOM_CREATED, &rtype::RTypeNetworkClient::roomCreated113DatagramHandler},
    {rtype::network::T_114_QUIT_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_115_ROOM_QUITTED, &rtype::RTypeNetworkClient::roomQuitted115DatagramHandler},
    {rtype::network::T_116_JOIN_ROOM, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_117_ROOM_JOINED, &rtype::RTypeNetworkClient::roomJoined117DatagramHandler},
    {rtype::network::T_200_ACTION, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_210_DISPLAY, &rtype::RTypeNetworkClient::display210DatagramHandler},
    {rtype::network::T_220_LIVING, &rtype::RTypeNetworkClient::living220DatagramHandler},
    {rtype::network::T_230_CHARGE, &rtype::RTypeNetworkClient::charge230DatagramHandler},
    {rtype::network::T_240_SCORE, &rtype::RTypeNetworkClient::score240DatagramHandler},
    {rtype::network::T_250_END_GAME, &rtype::RTypeNetworkClient::endGame250DatagramHandler},
    {rtype::network::T_260_GAME_ENDED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_270_GAME_STARTING, &rtype::RTypeNetworkClient::startGame270DatagramHandler},
    {rtype::network::T_280_GAME_STARTED, &rtype::RTypeNetworkClient::invalidDatagramHandler},
    {rtype::network::T_301_INVALID_PACKET, &rtype::RTypeNetworkClient::emptyDatagramHandler},
    {rtype::network::T_302_INVALID_PARAM, &rtype::RTypeNetworkClient::emptyDatagramHandler},
    {rtype::network::T_303_USERNAME_ALREADY_USED, &rtype::RTypeNetworkClient::error303DatagramHandler},
    {rtype::network::T_304_ROOM_NAME_ALREADY_USED, &rtype::RTypeNetworkClient::error304DatagramHandler},
    {rtype::network::T_305_NOT_IN_A_ROOM, &rtype::RTypeNetworkClient::emptyDatagramHandler},
    {rtype::network::T_306_UNKNOWN_ROOM, &rtype::RTypeNetworkClient::error306DatagramHandler},
    {rtype::network::T_307_INVALID_PASSWORD, &rtype::RTypeNetworkClient::error307DatagramHandler},
    {rtype::network::T_308_ROOM_FULL, &rtype::RTypeNetworkClient::error308DatagramHandler},
    {rtype::network::T_309_OPERATION_NOT_PERMITTED, &rtype::RTypeNetworkClient::emptyDatagramHandler},
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
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][100] Trying to connect to server " + _syncTo.getServerHost() + ":" + std::to_string(_syncTo.getServerPort()));
        } else if (_timeSinceLastServerReach > serverConnectivityPingThreshHold - 100) {
            _syncTo.setConnectionStatus(false, "Could not reach server");
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient] Connection failed: could not reach server");
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
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][110] Start get room");
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
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][112] Start create room");
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
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][116] Start join room");
        }
    }
    //quit lobby
    if (lobbyState.isQuittingLobby()) {
        if (_datagrams.find(rtype::network::T_114_QUIT_ROOM) == _datagrams.end() || !_datagrams[rtype::network::T_114_QUIT_ROOM].second.isValid()) {
            _datagrams[rtype::network::T_114_QUIT_ROOM].first = lobbyDatagramRetrySyncRate;
            dg.initSingleOpCodeDatagram(rtype::network::T_114_QUIT_ROOM);
            _datagrams[rtype::network::T_114_QUIT_ROOM].second = dg;
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][114] Start quit room");
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
    invalidateEntities(deltatime);
}

void rtype::RTypeNetworkClient::lostConnectionSequence([[maybe_unused]]long deltatime)
{
    _syncTo.setLostConnection(true);
}

void rtype::RTypeNetworkClient::checkLostConnection()
{
    if (_sequence == NS_LOST_CONNECTION)
        return;
    if (_timeSinceLastServerReach >= serverConnectivityPingThreshHold && _timeSinceLastServerReach < serverConnectionLostThreshHold) {
        if (_datagrams.find(rtype::network::T_102_PING) == _datagrams.end() || !_datagrams[rtype::network::T_102_PING].second.isValid()) {
            rtype::network::RTypeDatagram dg({_syncTo.getServerHost(), _syncTo.getServerPort()});
            dg.initSingleOpCodeDatagram(rtype::network::T_102_PING);
            _datagrams[rtype::network::T_102_PING].first = lobbyDatagramRetrySyncRate;
            _datagrams[rtype::network::T_102_PING].second = dg;
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][102] Starting to ping server to check living status");
        }
    } else if (_timeSinceLastServerReach >= serverConnectionLostThreshHold) {
        _sequence = NS_LOST_CONNECTION;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient] Connection to server lost");
    }
}

void rtype::RTypeNetworkClient::invalidateEntities([[maybe_unused]]long deltatime)
{
    std::vector<int> shouldDelete;
    std::chrono::high_resolution_clock::time_point currTime = std::chrono::high_resolution_clock::now();
    for (auto &entity : _syncTo.getEntities()) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currTime - entity.getLastDisplayUpdate()).count() >= entityInvalidateDisplayAfter) {
            entity.setShouldDisplay(false);
        } else {
            continue;
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currTime - entity.getLastUpdate()).count() >= entityInvalidateEntityAfter) {
            shouldDelete.push_back(entity.getId());
        }
    }
    for (auto &id: shouldDelete) {
        _syncTo.removeEntity(id);
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

void rtype::RTypeNetworkClient::connected101DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (!_syncTo.isConnnected() && _syncTo.isTryingToConnected()) {
        _syncTo.setConnectionStatus(true);
        resetDatagram(rtype::network::T_100_CONNECT);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][101] Connection successfull");
    }
}

void rtype::RTypeNetworkClient::ping102DatagramHandler(rtype::network::RTypeDatagram dg)
{
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_103_PONG);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][102] Sending 103 pong");
    _socket.lock()->send(response);
}

void rtype::RTypeNetworkClient::disconnected105DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.isConnnected()) {
        //_syncTo.disconnect(); //todo if needed
        resetDatagram(rtype::network::T_104_DISCONNECT);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][105] Disconnected");
    }
}

void rtype::RTypeNetworkClient::clientDisconnected106DatagramHandler(rtype::network::RTypeDatagram dg)
{
    std::string username;
    dg.extract106ClientDisconnectedDatagram(username);
    auto &lobbyState = _syncTo.getLobbyState();
    auto &playersInLobby = lobbyState.getPlayersInLobby();
    if (lobbyState.isInLobby() && std::find(playersInLobby.begin(), playersInLobby.end(), username) != playersInLobby.end()) {
        lobbyState.removeFromLobby(username);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][106] Client disconnected: " + username);
    }
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_107_OK_CLIENT_DISCONNECTED);
    _socket.lock()->send(response);
}

void rtype::RTypeNetworkClient::clientConnected108DatagramHandler(rtype::network::RTypeDatagram dg)
{
    std::string username;
    dg.extract108NewClientConnectedDatagram(username);
    auto &lobbyState = _syncTo.getLobbyState();
    auto &playersInLobby = lobbyState.getPlayersInLobby();
    if (lobbyState.isInLobby() && std::find(playersInLobby.begin(), playersInLobby.end(), username) != playersInLobby.end()) {
        lobbyState.addToLobby(username);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][108] Client connected: " + username);
    }
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_109_OK_NEW_CLIENT_CONNECTED);
    _socket.lock()->send(response);
}

void rtype::RTypeNetworkClient::roomList111DatagramHandler(rtype::network::RTypeDatagram dg)
{
    auto &lobbyState = _syncTo.getLobbyState();
    if (lobbyState.isUpdatingLobby()) {
        std::vector<rtype::network::RTypeDatagramRoom> rooms;
        std::vector<LobbyState::LobbyData> data;
        dg.extract111RoomListDatagram(rooms);
        for (auto room : rooms) {
            LobbyState::LobbyData parsed;
            parsed.name = room.name;
            parsed.nbPlayers = room.slotUsed;
            parsed.size = room.capacity;
            parsed.password = room.password;
            parsed.hasPassword = room.hasPassword;
            data.push_back(parsed);
        }
        lobbyState.setAvailableLobby(data);
        resetDatagram(rtype::network::T_110_GET_ROOMS);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][111] Received room update");
    }
}

void rtype::RTypeNetworkClient::roomCreated113DatagramHandler(rtype::network::RTypeDatagram dg)
{
    auto &lobbyState = _syncTo.getLobbyState();
    if (lobbyState.isCreatingLobby()) {
        lobbyState.validateCreate();
        resetDatagram(rtype::network::T_112_CREATE_ROOM);
        _sequence = NS_LOBBY;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][113] Room created");
    }
}

void rtype::RTypeNetworkClient::roomQuitted115DatagramHandler(rtype::network::RTypeDatagram dg)
{
    auto &lobbyState = _syncTo.getLobbyState();
    if (lobbyState.isQuittingLobby()) {
        lobbyState.validateQuit();
        resetDatagram(rtype::network::T_114_QUIT_ROOM);
        _sequence = NS_LOBBY;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][115] Room exited");
    }
}

void rtype::RTypeNetworkClient::roomJoined117DatagramHandler(rtype::network::RTypeDatagram dg)
{
    auto &lobbyState = _syncTo.getLobbyState();
    if (lobbyState.isJoiningLobby()) {
        std::vector<std::string> names;
        dg.extract117RoomJoinedDatagram(names);
        lobbyState.validateJoin(names);
        resetDatagram(rtype::network::T_116_JOIN_ROOM);
        _sequence = NS_LOBBY;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][117] Room Joined there is " + std::to_string(names.size()) + " players inside");
    }
}

void rtype::RTypeNetworkClient::display210DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (!_syncTo.isInGame())
        return;
    rtype::network::RTypeDatagramDisplay disp;
    dg.extract210DisplayDatagram(disp);
    try {
        auto &found = _syncTo.getEntity(disp.entityId);
        found.setShouldDisplay(true);
        found.setLastDisplayUpdate(std::chrono::high_resolution_clock::now());
        found.setLastUpdate(std::chrono::high_resolution_clock::now());
        found.setType(disp.type);
        found.setPos(disp.position.x, disp.position.y, disp.position.z);
        found.setRot(disp.rotation.x, disp.rotation.y);
        found.setScale(disp.scale.x, disp.scale.y);
    } catch (rtype::GameStateException &e) {
        EntitiesState state;
        state.setShouldDisplay(true);
        state.setLastDisplayUpdate(std::chrono::high_resolution_clock::now());
        state.setLastUpdate(std::chrono::high_resolution_clock::now());
        state.setType(disp.type);
        state.setPos(disp.position.x, disp.position.y, disp.position.z);
        state.setRot(disp.rotation.x, disp.rotation.y);
        state.setScale(disp.scale.x, disp.scale.y);
        state.setId(disp.entityId);
        state.setHp(-1);
        _syncTo.addEntity(state);
    }
}

void rtype::RTypeNetworkClient::living220DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (!_syncTo.isInGame())
        return;
    rtype::network::RTypeDatagramLiving living;
    dg.extract220LivingDatagram(living);
    try {
        auto &found = _syncTo.getEntity(living.entityId);
        found.setLastUpdate(std::chrono::high_resolution_clock::now());
        found.setHp(living.life);
    } catch (rtype::GameStateException &e) {
        EntitiesState state;
        state.setShouldDisplay(false);
        state.setLastDisplayUpdate(std::chrono::high_resolution_clock::now());
        state.setLastUpdate(std::chrono::high_resolution_clock::now());
        state.setType(0);
        state.setPos(0, 0, 0);
        state.setRot(0, 0);
        state.setScale(0, 0);
        state.setId(living.entityId);
        state.setHp(living.life);
        _syncTo.addEntity(state);
    }
}

void rtype::RTypeNetworkClient::charge230DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (!_syncTo.isInGame())
        return;
    unsigned char charge;
    dg.extract230ChargeDatagram(charge);
    _syncTo.setCharge(charge);
}

void rtype::RTypeNetworkClient::score240DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (!_syncTo.isInGame())
        return;
    rtype::network::RTypeDatagramScore score;
    dg.extract240ScoreDatagram(score);
    _syncTo.setScores(std::make_tuple(score.p1Score, score.p2Score, score.p3Score, score.p4Score));
}

void rtype::RTypeNetworkClient::endGame250DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.isInGame()) {
        _syncTo.setInGame(false);
        rtype::network::RTypeDatagramScore score;
        dg.extract250EndGameDatagram(score);
        _syncTo.setScores(std::make_tuple(score.p1Score, score.p2Score, score.p3Score, score.p4Score));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][250] Game ending");
    }
    if (_syncTo.isPlayAgain()) {
        rtype::network::RTypeDatagram response(dg.getHostInfos());
        response.initSingleOpCodeDatagram(rtype::network::T_260_GAME_ENDED);
        _socket.lock()->send(response);
    }
}

void rtype::RTypeNetworkClient::startGame270DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (!_syncTo.isInGame()) {
        _syncTo.setPlayAgain(false);
        _syncTo.setInGame(true);
        _sequence = NS_GAME;
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][270] Game starting");
    }
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_280_GAME_STARTED);
    _socket.lock()->send(response);
}

void rtype::RTypeNetworkClient::error303DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.isTryingToConnected()) {
        _syncTo.setConnectionStatus(false, "Username already used");
        resetDatagram(rtype::network::T_100_CONNECT);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][303] Failed to connect: username already used");
    }
}

void rtype::RTypeNetworkClient::error304DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.getLobbyState().isCreatingLobby()) {
        _syncTo.getLobbyState().invalidateCreate("Room name already used");
        resetDatagram(rtype::network::T_112_CREATE_ROOM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][304] Failed to create room: room name already used");
    }
}

void rtype::RTypeNetworkClient::error306DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.getLobbyState().isJoiningLobby()) {
        _syncTo.getLobbyState().invalidateJoin("Room not found");
        resetDatagram(rtype::network::T_116_JOIN_ROOM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][306] Failed to join room: room not found");
    }
}

void rtype::RTypeNetworkClient::error307DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.getLobbyState().isJoiningLobby()) {
        _syncTo.getLobbyState().invalidateJoin("Invalid password");
        resetDatagram(rtype::network::T_116_JOIN_ROOM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][306] Failed to join room: room not found");
    }
}

void rtype::RTypeNetworkClient::error308DatagramHandler(rtype::network::RTypeDatagram dg)
{
    if (_syncTo.getLobbyState().isJoiningLobby()) {
        _syncTo.getLobbyState().invalidateJoin("Room not joinable");
        resetDatagram(rtype::network::T_116_JOIN_ROOM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTypeNetworkClient][" + static_cast<std::string>(dg.getHostInfos()) + "][306] Failed to join room: room not joinable");
    }
}
