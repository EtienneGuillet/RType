/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeServer.hpp
*/

/* Created the 21/11/2019 at 17:59 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPESERVER_HPP
#define R_TYPE_RTYPESERVER_HPP

#include "network/INetworkManager.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class RTypeServer
     * @brief A class that represent a RType server
     */
    class RTypeServer {
    public:
        /*!
         * @brief ctor
         * @param port The port of the server to use
         */
        explicit RTypeServer(unsigned short port = 54321);
        /*!
         * @brief dtor
         */
        ~RTypeServer();

        /*!
         * @brief Cpy ctor deleted
         * @param other server to create from
         */
        RTypeServer(const RTypeServer &other) = delete;

        /*!
         * @brief assignment operator deleted
         * @param rhs server to assign to
         * @return *this
         */
        RTypeServer &operator=(const RTypeServer &rhs) = delete;

    public:
        /*!
         * @brief Run a frame of the server
         */
        void run();

    private:
        std::unique_ptr<b12software::network::INetworkManager> _networkManager; /*!< The network manager of this server */
        std::weak_ptr<b12software::network::udp::IUdpSocket> _socket; /*!< This server udp socket */
    };
}

#endif //R_TYPE_RTYPESERVER_HPP
