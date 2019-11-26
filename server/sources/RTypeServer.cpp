/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeServer.cpp
*/

/* Created the 21/11/2019 at 17:59 by julian.frabel@epitech.eu */

#include <exception/RTypeUnknownRoomException.hpp>
#include <exception/RTypeRoomAlreadyFullException.hpp>
#include <exception/RTypeInvalidPasswordException.hpp>
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
    {rtype::network::T_103_PONG, &rtype::RTypeServer::emptyDatagramHandler},
    {rtype::network::T_104_DISCONNECT, &rtype::RTypeServer::protocol104DisconnectDatagramHandler},
    {rtype::network::T_105_DISCONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_106_CLIENT_DISCONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_107_OK_CLIENT_DISCONNECTED, &rtype::RTypeServer::protocol107ClientDisconnectedDatagramHandler},
    {rtype::network::T_108_NEW_CLIENT_CONNECTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_109_OK_NEW_CLIENT_CONNECTED, &rtype::RTypeServer::protocol109NewClientConnectedDatagramHandler},
    {rtype::network::T_110_GET_ROOMS, &rtype::RTypeServer::protocol110GetRoomsDatagramHandler},
    {rtype::network::T_111_ROOM_LIST, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_112_CREATE_ROOM, &rtype::RTypeServer::protocol112CreateRoomsDatagramHandler},
    {rtype::network::T_113_ROOM_CREATED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_114_QUIT_ROOM, &rtype::RTypeServer::protocol114QuitRoomsDatagramHandler},
    {rtype::network::T_115_ROOM_QUITTED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_116_JOIN_ROOM, &rtype::RTypeServer::protocol116JoinRoomsDatagramHandler},
    {rtype::network::T_117_ROOM_JOINED, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_200_ACTION, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_210_DISPLAY, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_220_LIVING, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_230_CHARGE, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_240_SCORE, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_250_END_GAME, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_260_GAME_ENDED, &rtype::RTypeServer::invalidDatagramHandler}, //todo
    {rtype::network::T_270_GAME_STARTING, &rtype::RTypeServer::invalidDatagramHandler},
    {rtype::network::T_280_GAME_STARTED, &rtype::RTypeServer::invalidDatagramHandler}, //todo
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
      _clients(),
      _rooms()
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
    handleDatagrams();
    handleLiveness();
    handleLooping();
    cleanRooms();
}

void rtype::RTypeServer::handleDatagrams()
{
    auto locketSocket = _socket.lock();
    if (!locketSocket)
        return;
    while (locketSocket->hasPendingDatagrams()) {
        rtype::network::RTypeDatagram dg = locketSocket->receive();
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER] Received datagram from " + static_cast<std::string>(dg.getHostInfos()) + "(" + std::to_string(dg.getDatagramSize()) + " bytes)(code: " + std::to_string(dg.getType()) + ")");
        auto it = protocolMap.find(dg.getType());
        if (it != protocolMap.end()) {
            try {
                (this->*(it->second))(dg);
                updateClientLiveness(dg.getHostInfos());
            } catch (exceptions::DatagramMalformedException &e) {
                invalidDatagramHandler(dg);
            }
        } else {
            unknownDatagramHandler(dg);
        }
    }
}

void rtype::RTypeServer::handleLiveness()
{
    auto locketSocket = _socket.lock();
    if (!locketSocket)
        return;
    std::scoped_lock lock(_clients);
    auto now = Client::Clock::now();
    rtype::network::RTypeDatagram dg;
    dg.initSingleOpCodeDatagram(rtype::network::T_102_PING);
    std::vector<Client> toDisconnect;
    for (auto &client : _clients) {
        if (now - client.getLastReached() >= lostConnectionDuration && now - client.getClock(rtype::network::T_102_PING) >= timeBetweenDatagramsDuration) {
            dg.setDestination(client.getHost());
            locketSocket->send(dg);
            client.setClock(rtype::network::T_102_PING, now);
        }
        if (now - client.getLastReached() >= forceDisconnectDuration) {
            toDisconnect.push_back(client);
        }
    }
    for (auto &client : toDisconnect) {
        disconnectClient(client);
    }
}

void rtype::RTypeServer::handleLooping()
{
    auto locketSocket = _socket.lock();
    if (!locketSocket)
        return;
    std::scoped_lock lock(_clients);
    auto now = Client::Clock::now();
    for (auto &client : _clients) {
        auto types = client.getDatagramTypes();
        for (auto &type : types) {
            if (now - client.getClock(type) >= timeBetweenDatagramsDuration) {
                locketSocket->send(client.getDatagram(type));
                client.setClock(type, now);
            }
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

void rtype::RTypeServer::addNewClient(const rtype::Client &client)
{
    _clients.push_back(client);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER] Connected client " + static_cast<std::string>(client.getHost()) + " " + client.getUsername());
}

void rtype::RTypeServer::updateClientLiveness(const b12software::network::HostInfos &host)
{
    std::scoped_lock lock(_clients);
    for (auto &client : _clients) {
        if (client.getHost() == host) {
            client.setLastReached(rtype::Client::Clock::now());
            return;
        }
    }
}

void rtype::RTypeServer::disconnectClient(const rtype::Client &client)
{
    std::scoped_lock lock(_clients);
    _clients.remove_if([this, &client](const Client &elem) {
        if (client == elem) {
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER] Disconnected client " + static_cast<std::string>(elem.getHost()) + " " + elem.getUsername());
            exitRoom(getClientByHost(elem.getHost()));
            return true;
        }
        return false;
    });
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
    Client toAdd(dg.getHostInfos(), username);
    switch (invalidUsernameCode) {
    case 1:
        response.initSingleOpCodeDatagram(rtype::network::T_302_INVALID_PARAM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] Invalid username '" + username + "'");
        break;
    case 2:
        if (getClientByUsername(username) == toAdd) {
            response.initSingleOpCodeDatagram(rtype::network::T_101_CONNECTED);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] Re-sended OK to '" + username + "'");
        } else {
            response.initSingleOpCodeDatagram(rtype::network::T_303_USERNAME_ALREADY_USED);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] Already used username '" + username + "'");
        }
        break;
    default:
        response.initSingleOpCodeDatagram(rtype::network::T_101_CONNECTED);
        addNewClient(toAdd);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][100] A new client connected with username '" + username + "'");
        break;
    }
    _socket.lock()->send(response);
}

void rtype::RTypeServer::protocol104DisconnectDatagramHandler(rtype::network::RTypeDatagram dg)
{
    try {
        disconnectClient(getClientByHost(dg.getHostInfos()));
    } catch (exception::RTypeServerException &e) {}
    rtype::network::RTypeDatagram response(dg.getHostInfos());
    response.initSingleOpCodeDatagram(rtype::network::T_105_DISCONNECTED);
    _socket.lock()->send(response);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][104] Send disconnected to client");
}

void rtype::RTypeServer::emptyDatagramHandler(rtype::network::RTypeDatagram dg)
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][" + std::to_string(dg.getType()) + "] Empty handler");
}

rtype::Client &rtype::RTypeServer::getClientByHost(const b12software::network::HostInfos &host)
{
    std::scoped_lock lock(_clients);
    for (auto &client : _clients) {
        if (client.getHost() == host)
            return client;
    }
    throw exception::RTypeServerException("Client " + static_cast<std::string>(host) + " not found", WHERE);
}

rtype::Client &rtype::RTypeServer::getClientByUsername(const std::string &username)
{
    std::scoped_lock lock(_clients);
    for (auto &client : _clients) {
        if (client.getUsername() == username)
            return client;
    }
    throw exception::RTypeServerException("Client " + username + " not found", WHERE);
}

void rtype::RTypeServer::createRoom(const std::string &name, unsigned char capacity, bool hasPassword,
                                    const std::string &password)
{
    if (capacity <= 0)
        throw exception::RTypeServerException("Invalid capacity", WHERE);
    std::shared_ptr<Room> newRoom = std::make_shared<Room>();
    newRoom->setCapacity(capacity);
    newRoom->setGameRunning(false);
    newRoom->setHasPassword(hasPassword);
    newRoom->setName(name);
    newRoom->setPassword(password);
    newRoom->setSlotUsed(0);
    _rooms.push_back(newRoom);
}

void rtype::RTypeServer::joinRoom(const std::string &roomName, rtype::Client &client, const std::string &password)
{
    for (auto &room : _rooms) {
        if (room->getName() == roomName) {
            if (room->isGameRunning() || room->getSlotUsed() == room->getCapacity())
                throw exception::RTypeRoomAlreadyFullException("Room " + roomName + " is not joinable", WHERE);
            if (room->hasPassword() && room->getPassword() != password)
                throw exception::RTypeInvalidPasswordException("Invalid password", WHERE);
            room->applyToClients([client](Client &c) {
                network::RTypeDatagram datagram(c.getHost());
                datagram.init108NewClientConnectedDatagram(client.getUsername());
                c.setDatagram(rtype::network::T_108_NEW_CLIENT_CONNECTED, datagram);
            });
            room->addClient(client);
            client.setRoom(room);
            client.setClientState(CS_IN_ROOM);
            return;
        }
    }
    throw exception::RTypeUnknownRoomException("Room " + roomName + " not found", WHERE);
}

void rtype::RTypeServer::exitRoom(rtype::Client &client)
{
    if (client.getClientState() != CS_IN_LOBBY) {
        auto room = client.getRoom().lock();
        if (room) {
            room->removeClient(client);
            room->applyToClients([client](Client &c) {
                network::RTypeDatagram datagram(c.getHost());
                datagram.init106ClientDisconnectedDatagram(client.getUsername());
                c.setDatagram(rtype::network::T_106_CLIENT_DISCONNECTED, datagram);
            });
        }
        client.removeRoom();
        client.setClientState(CS_IN_LOBBY);
    }
}

void rtype::RTypeServer::cleanRooms()
{
    _rooms.remove_if([](const std::shared_ptr<Room> &elem) {
        if (elem->getSlotUsed() == 0) {
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER] Cleaning room " + elem->getName());
            return true;
        }
        return false;
    });
}

int rtype::RTypeServer::isInvalidRoomName(const std::string &name)
{
    if (name.empty())
        return 1;
    for (auto &room : _rooms) {
        if (room->getName() == name) {
            return 2;
        }
    }
    return 0;
}

void rtype::RTypeServer::protocol107ClientDisconnectedDatagramHandler(rtype::network::RTypeDatagram dg)
{
    try {
        Client &client = getClientByHost(dg.getHostInfos());
        client.setDatagram(network::T_106_CLIENT_DISCONNECTED, Client::defaultDg);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][107] Received");
    } catch (exception::RTypeServerException &e) {}
}

void rtype::RTypeServer::protocol109NewClientConnectedDatagramHandler(rtype::network::RTypeDatagram dg)
{
    try {
        Client &client = getClientByHost(dg.getHostInfos());
        client.setDatagram(network::T_108_NEW_CLIENT_CONNECTED, Client::defaultDg);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][109] Received");
    } catch (exception::RTypeServerException &e) {}
}

void rtype::RTypeServer::protocol110GetRoomsDatagramHandler(rtype::network::RTypeDatagram dg)
{
    network::RTypeDatagram response(dg.getHostInfos());
    try {
        getClientByHost(dg.getHostInfos());
    } catch (exception::RTypeServerException &e) {
        response.initSingleOpCodeDatagram(network::T_309_OPERATION_NOT_PERMITTED);
        _socket.lock()->send(response);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][110] Operation not permitted");
        return;
    }
    std::vector<rtype::network::RTypeDatagramRoom> dgRooms;
    for (auto &room : _rooms) {
        rtype::network::RTypeDatagramRoom dgRoom;
        dgRoom.hasPassword = room->hasPassword();
        dgRoom.capacity = room->getCapacity();
        dgRoom.name = room->getName();
        dgRoom.password = room->getPassword();
        dgRoom.slotUsed = room->getSlotUsed();
        dgRooms.push_back(dgRoom);
    }
    response.init111RoomListDatagram(dgRooms);
    _socket.lock()->send(response);
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][110] List sent");
}

void rtype::RTypeServer::protocol112CreateRoomsDatagramHandler(rtype::network::RTypeDatagram dg)
{
    network::RTypeDatagram response(dg.getHostInfos());
    try {
        getClientByHost(dg.getHostInfos());
    } catch (exception::RTypeServerException &e) {
        response.initSingleOpCodeDatagram(network::T_309_OPERATION_NOT_PERMITTED);
        _socket.lock()->send(response);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][112] Operation not permitted");
        return;
    }
    auto &client = getClientByHost(dg.getHostInfos());
    auto lockedRoom = client.getRoom().lock();
    network::RTypeDatagramRoom room;
    dg.extract112CreateRoomDatagram(room);
    int invalidCode = isInvalidRoomName(room.name);
    switch (invalidCode) {
    case 1:
        response.initSingleOpCodeDatagram(rtype::network::T_302_INVALID_PARAM);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][112] Invalid room name '" + room.name + "'");
        break;
    case 2:
        if (lockedRoom && lockedRoom->getName() == room.name) {
            response.initSingleOpCodeDatagram(rtype::network::T_113_ROOM_CREATED);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][112] Re-sended OK for room '" + room.name + "'");
        } else {
            response.initSingleOpCodeDatagram(rtype::network::T_304_ROOM_NAME_ALREADY_USED);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][112] Already used room name '" + room.name + "'");
        }
        break;
    default:
        response.initSingleOpCodeDatagram(rtype::network::T_113_ROOM_CREATED);
        createRoom(room.name, room.capacity, room.hasPassword, room.password);
        joinRoom(room.name, client, room.password);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][112] A new room was created '" + room.name + "'");
        break;
    }
    _socket.lock()->send(response);
}

void rtype::RTypeServer::protocol114QuitRoomsDatagramHandler(rtype::network::RTypeDatagram dg)
{
    network::RTypeDatagram response(dg.getHostInfos());
    try {
        exitRoom(getClientByHost(dg.getHostInfos()));
        response.initSingleOpCodeDatagram(network::T_115_ROOM_QUITTED);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][114] Client is not in a room anymore");
    } catch (exception::RTypeServerException &e) {
        response.initSingleOpCodeDatagram(network::T_309_OPERATION_NOT_PERMITTED);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][114] Operation not permitted");
    }
    _socket.lock()->send(response);
}

void rtype::RTypeServer::protocol116JoinRoomsDatagramHandler(rtype::network::RTypeDatagram dg)
{
    network::RTypeDatagram response(dg.getHostInfos());
    try {
        getClientByHost(dg.getHostInfos());
    } catch (exception::RTypeServerException &e) {
        response.initSingleOpCodeDatagram(network::T_309_OPERATION_NOT_PERMITTED);
        _socket.lock()->send(response);
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "[RTYPESERVER][" + static_cast<std::string>(dg.getHostInfos()) + "][114] Operation not permitted");
        return;
    }
    network::RTypeDatagramRoom room;
    dg.extract116JoinRoomDatagram(room);
    auto &client = getClientByHost(dg.getHostInfos());
    auto lockedRoom = client.getRoom().lock();
    try {
        if (!lockedRoom) {
            joinRoom(room.name, client, room.password);
            response.initSingleOpCodeDatagram(network::T_117_ROOM_JOINED);
        } else if (lockedRoom->getName() == room.name) {
            response.initSingleOpCodeDatagram(network::T_117_ROOM_JOINED);
        } else {
            exitRoom(client);
            joinRoom(room.name, client, room.password);
            response.initSingleOpCodeDatagram(network::T_117_ROOM_JOINED);
        }
    } catch (exception::RTypeUnknownRoomException &e) {
        response.initSingleOpCodeDatagram(network::T_306_UNKNOWN_ROOM);
    } catch (exception::RTypeInvalidPasswordException &e) {
        response.initSingleOpCodeDatagram(network::T_307_INVALID_PASSWORD);
    } catch (exception::RTypeRoomAlreadyFullException &e) {
        response.initSingleOpCodeDatagram(network::T_308_ROOM_FULL);
    }
    _socket.lock()->send(response);
}
