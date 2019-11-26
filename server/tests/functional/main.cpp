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

static void connect(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket, const std::string &username)
{
    std::cout << "Connect sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        dg.init100ConnectDatagram(username);
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_101_CONNECTED) {
            std::cout << "Connected" << std::endl;
            break;
        } else if (response.isValid()) {
            std::cout << "CODE " << response.getType() << std::endl;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_105_DISCONNECTED) {
            std::cout << "Disconnected" << std::endl;
            break;
        } else if (response.isValid()) {
            std::cout << "CODE " << response.getType() << std::endl;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_111_ROOM_LIST) {
            std::vector<rtype::network::RTypeDatagramRoom> rooms;
            response.extract111RoomListDatagram(rooms);
            for (auto &room : rooms) {
                std::cout << room.name << "(" << room.hasPassword << ") " << static_cast<int>(room.slotUsed) << "/" << static_cast<int>(room.capacity) << std::endl;
            }
            break;
        } else if (response.isValid()) {
            std::cout << "CODE " << response.getType() << std::endl;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_113_ROOM_CREATED) {
            std::cout << "Room created" << std::endl;
            break;
        } else if (response.isValid()) {
            std::cout << "CODE " << response.getType() << std::endl;
        }
    } while (true);
}

static void joinRoom(const b12software::network::HostInfos &serverHost, const std::shared_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    std::cout << "Join room sequence" << std::endl;
    rtype::network::RTypeDatagram dg(serverHost);
    do {
        rtype::network::RTypeDatagramRoom room = {"Room1", 3, 0, true, "password"};
        dg.init116JoinRoomDatagram(room);
        socket->send(dg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_117_ROOM_JOINED) {
            std::cout << "Room joined and is containing";
            std::vector<std::string> users;
            response.extract117RoomJoinedDatagram(users);
            for (auto &user : users) {
                std::cout << " " << user;
            }
            std::cout << std::endl;
            break;
        } else if (response.isValid()) {
            std::cout << "CODE " << response.getType() << std::endl;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rtype::network::RTypeDatagram response = socket->receive();
        if (response.isValid() && response.getType() == rtype::network::T_115_ROOM_QUITTED) {
            std::cout << "Room quited" << std::endl;
            break;
        } else if (response.isValid()) {
            std::cout << "CODE " << response.getType() << std::endl;
        }
    } while (true);
}

int main()
{
    std::unique_ptr<b12software::network::INetworkManager> networkManager(new b12software::network::asio::AsioNetworkManager());
    networkManager->start();
    std::weak_ptr<b12software::network::udp::IUdpSocket> _socket1 = networkManager->createNewUdpSocket();
    std::weak_ptr<b12software::network::udp::IUdpSocket> _socket2 = networkManager->createNewUdpSocket();
    auto socket1 = _socket1.lock();
    auto socket2 = _socket2.lock();
    if (!socket1 || !socket2) {
        std::cerr << "Socked couldn't be created" << std::endl;
        return 84;
    }
    socket1->bind(30001);
    socket2->bind(30002);
    b12software::network::HostInfos serverHost= {"0.0.0.0", 8080};
    connect(serverHost, socket1, "julian");
    connect(serverHost, socket2, "julian2");
    getRooms(serverHost, socket1);
    createRoom(serverHost, socket1);
    getRooms(serverHost, socket2);
    joinRoom(serverHost, socket2);
    getRooms(serverHost, socket1);
    quitRoom(serverHost, socket1);
    getRooms(serverHost, socket1);
    disconnect(serverHost, socket1);
    return 0;
}