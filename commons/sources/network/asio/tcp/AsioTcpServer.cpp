/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioTcpServer.cpp
*/

/* Created the 26/09/2019 at 11:37 by julian.frabel@epitech.eu */

#include "exception/NetworkException.hpp"
#include "logger/DefaultLogger.hpp"
#include "AsioTcpServer.hpp"
#include "network/asio/utils.hpp"

b12software::network::asio::AsioTcpServer::AsioTcpServer(boost::asio::io_context &context)
    : _context(context), _acceptor(_context), _clients(), _clientMapMutex(), _idVectorMutex(), _newIds(), _freeIds(), _disconnectedIds(), _maxId(0)
{

}

b12software::network::asio::AsioTcpServer::~AsioTcpServer()
{

}

void b12software::network::asio::AsioTcpServer::bind(int port)
{
    if (!_acceptor.is_open()) {
        try {
            _acceptor.open(boost::asio::ip::tcp::v4());
        } catch (boost::system::system_error &e) {
            logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioTcpServer] Failed to open socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
            throw exception::NetworkException(std::string("Failed to open socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
        }
    }
    try {
        _acceptor.bind(endpoint(boost::asio::ip::tcp::v4(), port));
    } catch (boost::system::system_error &e) {
        logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioTcpServer] Failed to bind: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
        throw exception::NetworkException(std::string("Failed to bind") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
    }
    try {
        _acceptor.listen();
    } catch (boost::system::system_error &e) {
        logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioTcpServer] Failed to listen: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
        throw exception::NetworkException(std::string("Failed to listen") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
    }
    startAccept();
}

void b12software::network::asio::AsioTcpServer::unbind()
{
    try {
        _acceptor.close();
    } catch (boost::system::system_error &e) {
        logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioTcpServer] Failed to close socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
        throw exception::NetworkException(std::string("Failed to close socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
    }
}

void b12software::network::asio::AsioTcpServer::disconnect(int clientId)
{
    lock lkI(_idVectorMutex);
    lock lkC(_clientMapMutex);
    auto it = _clients.find(clientId);
    if (it != _clients.end()) {
        it->second->disconnect();
        _disconnectedIds.push_back(it->first);
        auto newIt = std::find(_newIds.begin(), _newIds.end(), it->first);
        if (newIt != _newIds.end())
            _newIds.erase(newIt);
        _clients.erase(it);
    }
}

void b12software::network::asio::AsioTcpServer::sendToAll(const void *data, size_t size)
{
    lock lkC(_clientMapMutex);
    for (auto &pair : _clients) {
        pair.second->send(data, size);
    }
}

void b12software::network::asio::AsioTcpServer::sendToAll(const b12software::network::tcp::IPacket &packet)
{
    lock lkC(_clientMapMutex);
    for (auto &pair : _clients) {
        pair.second->send(packet);
    }
}

void b12software::network::asio::AsioTcpServer::sendToClient(int clientId, const void *data, size_t size)
{
    lock lkC(_clientMapMutex);
    auto it = _clients.find(clientId);
    if (it != _clients.end()) {
        it->second->send(data, size);
    }
}

void b12software::network::asio::AsioTcpServer::sendToClient(int clientId, const b12software::network::tcp::IPacket &packet)
{
    lock lkC(_clientMapMutex);
    auto it = _clients.find(clientId);
    if (it != _clients.end()) {
        it->second->send(packet);
    }
}

void b12software::network::asio::AsioTcpServer::sendToClients(const std::vector<int> &clientIds, const void *data, size_t size)
{
    lock lkC(_clientMapMutex);
    for (auto &id : clientIds) {
        auto it = _clients.find(id);
        if (it != _clients.end()) {
            it->second->send(data, size);
        }
    }
}

void b12software::network::asio::AsioTcpServer::sendToClients(const std::vector<int> &clientIds,
                                                        const b12software::network::tcp::IPacket &packet)
{
    lock lkC(_clientMapMutex);
    for (auto &id : clientIds) {
        auto it = _clients.find(id);
        if (it != _clients.end()) {
            it->second->send(packet);
        }
    }
}

void b12software::network::asio::AsioTcpServer::sendExceptClients(const std::vector<int> &exceptIds, const void *data, size_t size)
{
    lock lkC(_clientMapMutex);
    for (auto &pair : _clients) {
        if (std::find(exceptIds.begin(), exceptIds.end(), pair.first) == exceptIds.end())
            pair.second->send(data, size);
    }
}

void b12software::network::asio::AsioTcpServer::sendExceptClients(const std::vector<int> &exceptIds,
                                                            const b12software::network::tcp::IPacket &packet)
{
    lock lkC(_clientMapMutex);
    for (auto &pair : _clients) {
        if (std::find(exceptIds.begin(), exceptIds.end(), pair.first) == exceptIds.end())
            pair.second->send(packet);
    }
}

std::vector<int> b12software::network::asio::AsioTcpServer::getConnectedClientIds()
{
    lock lk(_clientMapMutex);
    std::vector<int> ret;
    for (auto &_client : _clients) {
        ret.push_back(_client.first);
    }
    return ret;
}

std::vector<int> b12software::network::asio::AsioTcpServer::getNewConnectedClientIds()
{
    lock lk(_idVectorMutex);
    std::vector<int> ret(_newIds);
    _newIds.clear();
    return ret;
}

std::vector<int> b12software::network::asio::AsioTcpServer::getDisconnectedClientIds()
{
    recomputeDisconnected();
    lock lkI(_idVectorMutex);
    std::vector<int> ret(_disconnectedIds);
    for (auto &id : _disconnectedIds) {
        _freeIds.push(id);
    }
    _disconnectedIds.clear();
    return ret;
}

std::weak_ptr<b12software::network::tcp::ITcpClient> b12software::network::asio::AsioTcpServer::getClientById(int clientId)
{
    lock lk(_clientMapMutex);
    auto it = _clients.find(clientId);
    if (it != _clients.end()) {
        return it->second;
    }
    return std::weak_ptr<b12software::network::tcp::ITcpClient>();
}

void b12software::network::asio::AsioTcpServer::startAccept()
{
    boost::shared_ptr<AsioTcpClient> client(new AsioTcpClient(_context));
    _acceptor.async_accept(
        client->getSocket(),
        std::bind(&AsioTcpServer::handleAccept, this, client, std::placeholders::_1)
    );
    logger::DefaultLogger::Log(logger::LogLevelDebug, "[AsioTcpServer] Start accepting");
}

void b12software::network::asio::AsioTcpServer::handleAccept(boost::shared_ptr<AsioTcpClient> client,
                                                             const boost::system::error_code &error)
{
    if (error == boost::asio::error::operation_aborted) {
        logger::DefaultLogger::Log(logger::LogLevelInfo, "[AsioTcpServer] Operation aborted (this is due to an async operation still beeing queued while socket is closing.");
        return;
    }
    if (!error) {
        lock lkI(_idVectorMutex);
        lock lkC(_clientMapMutex);
        int id = _maxId + 1;
        if (!_freeIds.empty()) {
            id = _freeIds.front();
            _freeIds.pop();
        } else {
            _maxId++;
        }
        _newIds.push_back(id);
        client->recompute();
        _clients.emplace(id, make_shared_ptr(client));
        logger::DefaultLogger::Log(logger::LogLevelDebug, "[AsioTcpServer] Accepted ID: " + std::to_string(id));
        startAccept();
    } else {
        logger::DefaultLogger::Log(logger::LogLevelError, "[AsioTcpServer] Failed to accept: " + error.message());
    }
}

void b12software::network::asio::AsioTcpServer::recomputeDisconnected()
{
    lock lkI(_idVectorMutex);
    lock lkC(_clientMapMutex);
    for (auto it = _clients.begin(); it != _clients.end(); ) {
        auto curr = it;
        it++;
        if (!curr->second->isConnected()) {
            _disconnectedIds.push_back(curr->first);
            auto newIt = std::find(_newIds.begin(), _newIds.end(), curr->first);
            if (newIt != _newIds.end())
                _newIds.erase(newIt);
            _clients.erase(curr);
        }
    }
}
