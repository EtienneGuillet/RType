/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** main.cpp
*/

/* Created the 26/11/2019 at 14:59 by julian.frabel@epitech.eu */

#include <iostream>
#include "rtype/network/RTypeDatagram.hpp"
#include "network/asio/AsioNetworkManager.hpp"

static void connect(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    std::cout << "Connect sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        dg.init100ConnectDatagram("julian");
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_101_CONNECTED) {
            std::cout << "Connected" << std::endl;
            break;
        }
    } while (true);
}

static void disconnect(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    std::cout << "Disconnect sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        dg.initSingleOpCodeDatagram(rtype::network::T_104_DISCONNECT);
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_105_DISCONNECTED) {
            std::cout << "Disconnected" << std::endl;
            break;
        }
    } while (true);
}

static void getRooms(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    std::cout << "Get rooms sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        dg.initSingleOpCodeDatagram(rtype::network::T_110_GET_ROOMS);
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_111_ROOM_LIST) {
            std::vector<rtype::network::RTypeDatagramRoom> rooms;
            response.extract111RoomListDatagram(rooms);
            for (auto &room : rooms) {
                std::cout << room.name << "(" << room.password << ") " << room.slotUsed << "/" << room.capacity << std::endl;
            }
            break;
        }
    } while (true);
}

static void createRoom(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    std::cout << "Create room sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        rtype::network::RTypeDatagramRoom room = {"Room1", 3, 0, true, "password"};
        dg.init112CreateRoomDatagram(room);
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_113_ROOM_CREATED) {
            std::cout << "Room created" << std::endl;
            break;
        }
    } while (true);
}

static void quitRoom(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    std::cout << "Quiting room sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        dg.initSingleOpCodeDatagram(rtype::network::T_114_QUIT_ROOM);
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_115_ROOM_QUITTED) {
            std::cout << "Room quited" << std::endl;
            break;
        }
    } while (true);
}

int main()
{
    std::unique_ptr<b12software::network::INetworkManager> networkManager(new b12software::network::asio::AsioNetworkManager());
    networkManager->start();
    std::weak_ptr<b12software::network::udp::IUdpSocket> _socket = networkManager->createNewUdpSocket();
    auto socket = _socket.lock();
    if (!socket) {
        std::cerr << "Socked couldn't be created" << std::endl;
        return 84;
    }
    socket->bind(30001);
    b12software::network::HostInfos serverHost= {"0.0.0.0", 8080};
    connect(serverHost, socket);
    getRooms(serverHost, socket);
    createRoom(serverHost, socket);
    getRooms(serverHost, socket);
    quitRoom(serverHost, socket);
    getRooms(serverHost, socket);
    disconnect(serverHost, socket);
    return 0;
}