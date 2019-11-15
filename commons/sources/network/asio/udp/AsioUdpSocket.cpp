/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioUdpSocket.cpp
*/

/* Created the 26/09/2019 at 11:42 by julian.frabel@epitech.eu */

#include <boost/bind.hpp>
#include "logger/DefaultLogger.hpp"
#include "AsioUdpSocket.hpp"
#include "exception/NetworkException.hpp"

b12software::network::asio::AsioUdpSocket::AsioUdpSocket(boost::asio::io_context &context)
    : _context(context), _socket(context), _datagrams(), _defaultHost({"", 0})
{

}

void b12software::network::asio::AsioUdpSocket::bind(int port)
{
    if (!_socket.is_open()) {
        try {
            _socket.open(boost::asio::ip::udp::v4());
        } catch (boost::system::system_error &e) {
            logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioUdpSocket] Failed to open socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
            throw exception::NetworkException(std::string("Failed to open socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
        }
    }
    try {
        _socket.bind(endpoint(boost::asio::ip::udp::v4(), port));
    } catch (boost::system::system_error &e) {
        logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioUdpSocket] Failed to bind: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
        throw exception::NetworkException(std::string("Failed to bind: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
    }
    startReceiving();
}

void b12software::network::asio::AsioUdpSocket::unbind()
{
    try {
        _socket.cancel();
        _socket.close();
    } catch (boost::system::system_error &e) {
        logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioUdpSocket] Failed to close socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
        throw exception::NetworkException(std::string("Failed to close socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
    }
}

void b12software::network::asio::AsioUdpSocket::registerHost(const b12software::network::HostInfos &infos)
{
    _defaultHost = infos;
}

void b12software::network::asio::AsioUdpSocket::unregisterHost()
{
    _defaultHost = {"", 0};
}

void b12software::network::asio::AsioUdpSocket::send(const void *data, size_t size, const b12software::network::HostInfos &infos)
{
    send(udp::Datagram(infos, data, size));
}

void b12software::network::asio::AsioUdpSocket::send(const b12software::network::udp::Datagram &datagram)
{
    b12software::network::HostInfos toUse = datagram.getHostInfos();
    if (!_defaultHost.host.empty()) {
        toUse = _defaultHost;
    }

    std::shared_ptr<udp::Datagram> message(new udp::Datagram(datagram));

    boost::asio::ip::udp::resolver resolver(_context);
    endpoint sendTo = resolver.resolve(toUse.host, std::to_string(toUse.port))->endpoint();
    _socket.async_send_to(
        boost::asio::buffer(message->getData(), message->getDatagramSize()),
        sendTo,
        boost::bind(&AsioUdpSocket::sendHandler, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

b12software::network::udp::Datagram b12software::network::asio::AsioUdpSocket::receive()
{
    udp::Datagram ret;
    if (hasPendingDatagrams()) {
        ret = _datagrams.front();
        _datagrams.pop();
    }
    return ret;
}

bool b12software::network::asio::AsioUdpSocket::hasPendingDatagrams() const
{
    return !_datagrams.empty();
}

int b12software::network::asio::AsioUdpSocket::getPort() const
{
    return _socket.local_endpoint().port();
}

std::string b12software::network::asio::AsioUdpSocket::getAddress() const
{
    return _socket.local_endpoint().address().to_string();
}

void b12software::network::asio::AsioUdpSocket::startReceiving()
{
    std::shared_ptr<std::array<char, maxReceiveDatagramSize>> buffer(new std::array<char, maxReceiveDatagramSize>());
    std::shared_ptr<AsioUdpSocket::endpoint> endp(new AsioUdpSocket::endpoint());
    _socket.async_receive_from(
        boost::asio::buffer(*buffer),
        *endp,
        boost::bind(&AsioUdpSocket::receiveHandler, this, buffer, endp, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

void b12software::network::asio::AsioUdpSocket::sendHandler([[maybe_unused]]const std::shared_ptr<udp::Datagram> &message,
                                                      const boost::system::error_code &error,
                                                      [[maybe_unused]]size_t byteTransferred)
{
    if (error == boost::asio::error::operation_aborted) {
        logger::DefaultLogger::Log(logger::LogLevelInfo, "[AsioUdpSocket] Operation aborted (this is due to an async operation still beeing queued while socket is closing.");
        return;
    }
    if (!error) {

    } else {
        logger::DefaultLogger::Log(logger::LogLevelError, "[AsioUdpSocket] Failed to deliver message: " + error.message());
    }
}

void b12software::network::asio::AsioUdpSocket::receiveHandler(const std::shared_ptr<std::array<char, maxReceiveDatagramSize>> &array,
                                                         const std::shared_ptr<AsioUdpSocket::endpoint> &endp,
                                                         const boost::system::error_code &error, size_t byteReceived)
{
    if (error == boost::asio::error::operation_aborted) {
        logger::DefaultLogger::Log(logger::LogLevelInfo, "[AsioUdpSocket] Operation aborted (this is due to an async operation still beeing queued while socket is closing.");
        return;
    }
    if (!error) {
        HostInfos host = {endp->address().to_string(), endp->port()};
        _datagrams.push(udp::Datagram(host, array->data(), byteReceived));
        startReceiving();
    } else {
        logger::DefaultLogger::Log(logger::LogLevelError, "[AsioUdpSocket] Error when receiving a datagram: " + error.message());
    }
}
