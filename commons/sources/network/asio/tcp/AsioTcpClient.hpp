/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** AsioTcpClient.hpp
*/

/* Created the 26/09/2019 at 11:27 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_ASIOTCPCLIENT_HPP
#define B12NETWORKING_ASIOTCPCLIENT_HPP

#include <boost/asio.hpp>
#include "network/tcp/ITcpClient.hpp"
#include "containers/ThreadSafeCircularBuffer.hpp"

namespace b12software::network {

    /*!
     * @namespace b12software::asio
     * @brief Main namespace for networking with boost asio
     */
    namespace asio {

        /*!
         * @class AsioTcpClient
         * @brief Boost asio implementation of a tcp client
         */
        class AsioTcpClient : public b12software::network::tcp::ITcpClient {
        private:
            using socket = boost::asio::ip::tcp::socket;
            using endpoint = boost::asio::ip::tcp::endpoint;
            using byte = unsigned char;


        public:
            /*!
             * @brief ctor
             * @param context boost context
             */
            explicit AsioTcpClient(boost::asio::io_context &context);
            /*!
             * @brief dtor
             */
            ~AsioTcpClient() override;

            /*!
             * @brief cpy ctor
             */
            AsioTcpClient(const AsioTcpClient &other) = delete;

            /*!
             * @brief Assignment operator
             * @param rhs client to assign to
             * @return *this
             */
            AsioTcpClient &operator=(const AsioTcpClient &rhs) = delete;

            static constexpr size_t bufferSizeInBytes = 4096;

        public:
            void connect(const HostInfos &infos) override;
            void disconnect() override;
            bool isConnected() const override;
            const HostInfos &getHostInfos() const override;
            const HostInfos &getSelfInfos() const override;
            size_t send(const void *data, size_t size) override;
            void send(const tcp::IPacket &packet) override;
            size_t receive(void *data, size_t size) override;
            void receive(tcp::IPacket &packet) override;
            size_t getAvailableBytesSize() const override;

        public:
            /*!
             * @brief Get the internal socket
             * @return The internal socket
             */
            socket &getSocket();

            /*!
             * @brief Recompute internal data for this client
             */
            void recompute();

        private:
            /*!
             * @brief Start the reception of data from boost asio
             */
            void startReceive();
            /*!
             * @brief Connect callback function
             * @param error A Boost error describing if an error occurred
             * @param endpointIterator The next endpoint to try in case of an error
             *
             * WARNING: this function will be called from the network thread NOT the main thread
             */
            void handleConnect(const boost::system::error_code &error, boost::asio::ip::tcp::resolver::iterator endpointIterator);
            /*!
             * @brief Handler called by boost asio when some data was sent
             * @param message A shared pointer containing the data that was sent (when the callback return the data is destroyed)
             * @param error Boost error that indicate the return of this send action
             * @param byteTransferred The number of bytes transferred
             *
             * WARNING: this function will be called from the network thread NOT the main thread
             */
            void handleSend(const std::shared_ptr<byte[]> &message, const boost::system::error_code &error, size_t byteTransferred);
            /*!
             * @brief Handler called by boost asio when some data was received
             * @param message A shared pointer containing the data that was received (when the callback return the data is destroyed)
             * @param error Boost error that indicate the return of this send action
             * @param byteTransferred The number of bytes in message
             *
             * WARNING: this function will be called from the network thread NOT the main thread
             */
            void handleReceive(const std::shared_ptr<byte[]> &message, const boost::system::error_code &error, size_t byteTransferred);

        private:
            boost::asio::io_context &_context; /*!< The boost asio io context */
            socket _socket; /*!< The tcp socket */
            HostInfos _distantInfos; /*!< Information about the distant host */
            HostInfos _selfInfos; /*!< Information about the distant host */
            containers::ThreadSafeCircularBuffer _buffer; /*!< The input buffer */
        };
    }
}

#endif //B12NETWORKING_ASIOTCPCLIENT_HPP
