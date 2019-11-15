/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioNetworkManager.cpp
*/

/* Created the 26/09/2019 at 11:19 by julian.frabel@epitech.eu */

#include "AsioNetworkManager.hpp"
#include "network/asio/udp/AsioUdpSocket.hpp"
#include "network/asio/tcp/AsioTcpClient.hpp"
#include "network/asio/tcp/AsioTcpServer.hpp"
#include "logger/DefaultLogger.hpp"

b12software::network::asio::AsioNetworkManager::AsioNetworkManager()
    : _ioContext(), _worker(), _udpSockets(), _tcpClients(), _tcpServers(), _networkThread(), _started(false)
{
    logger::DefaultLogger::Log(logger::LogLevelDebug, "[AsioNetworkManager] Created network manager");
}

b12software::network::asio::AsioNetworkManager::~AsioNetworkManager()
{
    stop();
    logger::DefaultLogger::Log(logger::LogLevelDebug, "[AsioNetworkManager] Destroyed network manager");
}

void b12software::network::asio::AsioNetworkManager::start()
{
    if (_started)
        return;
    _worker = new boost::asio::io_context::work(_ioContext);
    _networkThread = std::thread(&networkingThreadFunc, this);
    _started = true;
}

void b12software::network::asio::AsioNetworkManager::stop()
{
    if (!_started)
        return;
    _udpSockets.clear();
    _tcpClients.clear();
    _tcpServers.clear();
    delete _worker;
    _networkThread.join();
    _started = false;
}

void b12software::network::asio::AsioNetworkManager::networkingThreadFunc(AsioNetworkManager *manager)
{
    logger::DefaultLogger::Log(logger::LogLevelDebug, "[AsioNetworkManager] Started network thread");
    manager->_ioContext.run();
    logger::DefaultLogger::Log(logger::LogLevelDebug, "[AsioNetworkManager] Network thread terminating");
}

std::weak_ptr<b12software::network::udp::IUdpSocket> b12software::network::asio::AsioNetworkManager::createNewUdpSocket()
{
    if (!_started)
        return std::weak_ptr<udp::IUdpSocket>();
    return _udpSockets.emplace_back(new AsioUdpSocket(_ioContext));
}

std::weak_ptr<b12software::network::tcp::ITcpClient> b12software::network::asio::AsioNetworkManager::createNewTcpClient()
{
    if (!_started)
        return std::weak_ptr<tcp::ITcpClient>();
    return _tcpClients.emplace_back(new AsioTcpClient(_ioContext));
}

std::weak_ptr<b12software::network::tcp::ITcpServer> b12software::network::asio::AsioNetworkManager::createNewTcpServer()
{
    if (!_started)
        return std::weak_ptr<tcp::ITcpServer>();
    return _tcpServers.emplace_back(new AsioTcpServer(_ioContext));
}

void b12software::network::asio::AsioNetworkManager::destroyUdpSocket(const std::weak_ptr<b12software::network::udp::IUdpSocket> &socket)
{
    auto it = std::find(_udpSockets.begin(), _udpSockets.end(), socket);
    if (it != _udpSockets.end()) {
        _udpSockets.erase(it);
    }
}

void b12software::network::asio::AsioNetworkManager::destroyTcpClient(const std::weak_ptr<b12software::network::tcp::ITcpClient> &client)
{
    auto it = std::find(_tcpClients.begin(), _tcpClients.end(), client);
    if (it != _tcpClients.end()) {
        _tcpClients.erase(it);
    }
}

void b12software::network::asio::AsioNetworkManager::destroyTcpServer(const std::weak_ptr<b12software::network::tcp::ITcpServer> &server)
{
    auto it = std::find(_tcpServers.begin(), _tcpServers.end(), server);
    if (it != _tcpServers.end()) {
        _tcpServers.erase(it);
    }
}
