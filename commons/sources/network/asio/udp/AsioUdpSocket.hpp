/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioUdpSocket.hpp
*/

/* Created the 26/09/2019 at 11:42 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_ASIOUDPSOCKET_HPP
#define B12NETWORKING_ASIOUDPSOCKET_HPP

#include <boost/asio.hpp>
#include "network/udp/IUdpSocket.hpp"
#include "containers/ThreadSafeQueue.hpp"

namespace b12software::network {

    /*!
     * @namespace b12software::asio
     * @brief Main namespace for networking with boost asio
     */
    namespace asio {

        /*!
         * @class AsioUdpSocket
         * @brief Boost asio implementation of a udp socket
         */
        class AsioUdpSocket : public b12software::network::udp::IUdpSocket {
        public:
            /*!
             * @brief ctor
             */
            explicit AsioUdpSocket(boost::asio::io_context &context);
            /*!
             * @brief dtor
             */
            ~AsioUdpSocket() override = default;

            /*!
             * @brief cpy ctor
             */
            AsioUdpSocket(const AsioUdpSocket &other) = delete;

            /*!
             * @brief Assignment operator
             * @param rhs socket to assign to
             * @return *this
             */
            AsioUdpSocket &operator=(const AsioUdpSocket &rhs) = delete;

        public:
            void bind(unsigned short port) override;
            void unbind() override;
            void registerHost(const HostInfos &infos) override;
            void unregisterHost() override;
            void send(const void *data, size_t size, const HostInfos &infos) override;
            void send(const udp::Datagram &datagram) override;
            udp::Datagram receive() override;
            bool hasPendingDatagrams() const override;
            unsigned short getPort() const override;
            std::string getAddress() const override;

        private:
            static constexpr size_t maxReceiveDatagramSize = 1024; /*!< The maximum allowed size for a datagram packet */
            using socket = boost::asio::ip::udp::socket;
            using endpoint = boost::asio::ip::udp::endpoint;

        private:
            /*!
             * @brief Function that launch an async operation that receive a datagram
             */
            void startReceiving();
            /*!
             * @brief Handler called by boost asio when some data was sent
             * @param message A shared pointer containing the datagram that was sent (when the callback return the datagram is destroyed)
             * @param error Boost error that indicate the return of this send action
             * @param byteTransferred The number of bytes transferred
             *
             * WARNING: this function will be called from the network thread NOT the main thread
             */
            void sendHandler(const std::shared_ptr<udp::Datagram> &message, const boost::system::error_code &error, size_t byteTransferred);
            /*!
             * @brief Handler called by boost asio when some data is received
             * @param array The data received (will be destroyed when the callback return)
             * @param endpoint The endpoint from which the data was sent
             * @param error Boost error that indicate the return of this receive action
             * @param byteReceived The amount of byte contained in array
             *
             * WARNING: this function will be called from the network thread NOT the main thread
             */
            void receiveHandler(const std::shared_ptr<std::array<char, maxReceiveDatagramSize>> &array, const std::shared_ptr<AsioUdpSocket::endpoint> &endpoint, const boost::system::error_code &error, size_t byteReceived);

        private:

            boost::asio::io_context &_context; /*!< The context of this socket */
            socket _socket; /*!< The socket connected to the network */
            containers::ThreadSafeQueue<udp::Datagram> _datagrams; /*!< The datagram received from the network */
            HostInfos _defaultHost; /*!< The default host to which send the datagrams by default */
        };
    }
}
#endif //B12NETWORKING_ASIOUDPSOCKET_HPP
