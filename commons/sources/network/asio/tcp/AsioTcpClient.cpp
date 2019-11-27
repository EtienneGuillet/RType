/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioTcpClient.cpp
*/

/* Created the 26/09/2019 at 11:27 by julian.frabel@epitech.eu */

#include "AsioTcpClient.hpp"
#include "logger/DefaultLogger.hpp"
#include "exception/NetworkException.hpp"

b12software::network::asio::AsioTcpClient::AsioTcpClient(boost::asio::io_context &context)
    : _context(context), _socket(context), _distantInfos({"", 0}), _selfInfos({"", 0}), _buffer(bufferSizeInBytes)
{

}

b12software::network::asio::AsioTcpClient::~AsioTcpClient()
{

}

void b12software::network::asio::AsioTcpClient::connect(const b12software::network::HostInfos &infos)
{
    if (!_socket.is_open()) {
        try {
            _socket.open(boost::asio::ip::tcp::v4());
        } catch (boost::system::system_error &e) {
            logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioTcpClient] Failed to open socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
            throw exception::NetworkException(std::string("Failed to open socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
        }
    }
    boost::asio::ip::tcp::resolver resolver(_context);
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(infos.host, std::to_string(infos.port));
    _distantInfos = {"", 0};
    _selfInfos = {"", 0};
    endpoint endPoint = *it;
    _socket.async_connect(endPoint, std::bind(&AsioTcpClient::handleConnect, this, std::placeholders::_1, ++it));
}

void b12software::network::asio::AsioTcpClient::disconnect()
{
    _distantInfos = {"", 0};
    _selfInfos = {"", 0};
    try {
        _socket.close();
    } catch (boost::system::system_error &e) {
        logger::DefaultLogger::Log(logger::LogLevelError, std::string("[AsioTcpClient] Failed to close socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]");
        throw exception::NetworkException(std::string("Failed to close socket: ") + e.what() + " [" + std::to_string(e.code().value()) + "(" + e.code().message() + ")]", WHERE);
    }
}

bool b12software::network::asio::AsioTcpClient::isConnected() const
{
    return !_distantInfos.host.empty();
}

const b12software::network::HostInfos &b12software::network::asio::AsioTcpClient::getHostInfos() const
{
    return _distantInfos;
}

const b12software::network::HostInfos &b12software::network::asio::AsioTcpClient::getSelfInfos() const
{
    return _selfInfos;
}

size_t b12software::network::asio::AsioTcpClient::send(const void *data, size_t size)
{
    std::shared_ptr<byte[]> message(new byte[size]);
    std::memcpy(message.get(), data, size);
    _socket.async_send(
        boost::asio::buffer(message.get(), size),
        std::bind(&AsioTcpClient::handleSend, this, message, std::placeholders::_1, std::placeholders::_2)
    );
    return 0;
}

void b12software::network::asio::AsioTcpClient::send(const b12software::network::tcp::IPacket &packet)
{
    if (packet.isValid())
        send(packet.getData(), packet.getSize());
}

size_t b12software::network::asio::AsioTcpClient::receive(void *data, size_t size)
{
    return _buffer.read(static_cast<byte *>(data), size);
}

void b12software::network::asio::AsioTcpClient::receive(b12software::network::tcp::IPacket &packet)
{
    packet.clear();
    std::scoped_lock lock(_buffer);
    byte tmp[bufferSizeInBytes];
    size_t bufferedBytes = _buffer.read(tmp, bufferSizeInBytes);
    size_t retrievedData = packet.setData(tmp, bufferedBytes);
    if (retrievedData != bufferedBytes) {
        size_t diff = bufferedBytes - retrievedData;
        _buffer.write(tmp + retrievedData, diff);
    }
}

size_t b12software::network::asio::AsioTcpClient::getAvailableBytesSize() const
{
    return _buffer.getNbBufferedBytes() * sizeof(byte);
}

void b12software::network::asio::AsioTcpClient::startReceive()
{
    std::shared_ptr<byte[]> message(new byte[bufferSizeInBytes]);
    _socket.async_receive(
        boost::asio::buffer(message.get(), bufferSizeInBytes),
        std::bind(&AsioTcpClient::handleReceive, this, message, std::placeholders::_1, std::placeholders::_2)
    );
}

void b12software::network::asio::AsioTcpClient::handleConnect(const boost::system::error_code &error,
                                                        boost::asio::ip::tcp::resolver::iterator endpointIterator)
{
    if (error == boost::asio::error::operation_aborted) {
        logger::DefaultLogger::Log(logger::LogLevelInfo, "[AsioTcpClient] Operation aborted (this is due to an async operation still beeing queued while socket is closing).");
        return;
    }
    if (!error) {
        recompute();
    } else if (endpointIterator != boost::asio::ip::tcp::resolver::iterator()) {
        _socket.close();
        endpoint endPoint = *endpointIterator;
        _socket.async_connect(endPoint, std::bind(&AsioTcpClient::handleConnect, this, std::placeholders::_1, ++endpointIterator));
    } else {
        logger::DefaultLogger::Log(logger::LogLevelError, "[AsioTcpClient] Failed to connect to server: " + error.message());
    }
}

void b12software::network::asio::AsioTcpClient::handleSend([[maybe_unused]]const std::shared_ptr<byte[]> &message,
                                                     const boost::system::error_code &error,
                                                     [[maybe_unused]]size_t byteTransferred)
{
    if (error == boost::asio::error::operation_aborted) {
        logger::DefaultLogger::Log(logger::LogLevelInfo, "[AsioTcpClient] Operation aborted (this is due to an async operation still beeing queued while socket is closing).");
        return;
    }
    if (!error) {

    } else {
        logger::DefaultLogger::Log(logger::LogLevelError, "[AsioTcpClient] Failed to send data: " + error.message());
        disconnect();
    }
}

void b12software::network::asio::AsioTcpClient::handleReceive(const std::shared_ptr<byte[]> &message,
                                                        const boost::system::error_code &error,
                                                        size_t byteTransferred)
{
    if (error == boost::asio::error::operation_aborted) {
        logger::DefaultLogger::Log(logger::LogLevelInfo, "[AsioTcpClient] Operation aborted (this is due to an async operation still beeing queued while socket is closing).");
        return;
    }
    if (!error) {
        if (_buffer.write(message.get(), byteTransferred)) {
            logger::DefaultLogger::Log(logger::LogLevelWarn, "[AsioTcpClient] Internal buffer overflowed, some data was lost");
        }
        startReceive();
    } else {
        logger::DefaultLogger::Log(logger::LogLevelError, "[AsioTcpClient] Failed to receive data: " + error.message());
        disconnect();
    }
}

b12software::network::asio::AsioTcpClient::socket &b12software::network::asio::AsioTcpClient::getSocket()
{
    return _socket;
}

void b12software::network::asio::AsioTcpClient::recompute()
{
    _distantInfos = {_socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port()};
    _selfInfos = {_socket.local_endpoint().address().to_string(), _socket.local_endpoint().port()};
    startReceive();
}
