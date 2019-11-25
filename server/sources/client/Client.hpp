/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Client.hpp
*/

/* Created the 22/11/2019 at 18:21 by julian.frabel@epitech.eu */

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP

#include "ClientState.hpp"
#include "network/HostInfos.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {
    /*!
     * @class Client
     * @brief A class that represent a network connection
     */
    class Client {
    public:
        /*!
         * @brief ctor
         */
        Client();
        /*!
         * @brief ctor used to initialize a client with a host and username
         * @param host the host of the client
         * @param username the username of the client
         * @param state an optional state for the client (default to CS_IN_LOBBY)
         */
        Client(const b12software::network::HostInfos &host, const std::string &username, ClientState state = CS_IN_LOBBY);
        /*!
         * @brief dtor
         */
        ~Client() = default;
        /*!
         * @brief cpy ctor
         * @param other the element to copy
         */
        Client(const Client &other) = default;

        /*!
         * @brief Assignment operator
         * @param rhs The element to assign to
         * @return *this
         */
        Client &operator=(const Client &rhs) = default;

    public:
        /*!
         * @brief set the host of the client
         * @param host The host
         */
        void setHost(const b12software::network::HostInfos &host);
        /*!
         * @brief Get the host of the client
         * @return the host this client is related to
         */
        const b12software::network::HostInfos &getHost() const;
        /*!
         * @brief Get the username
         * @return the username
         */
        const std::string &getUsername() const;
        /*!
         * @brief set the username
         * @param username the username to set
         */
        void setUsername(const std::string &username);

        /*!
         * @brief Get the state of this client
         * @return the state of this client
         */
        ClientState getClientState() const;

        /*!
         * @brief Set the state of this client
         * @param state the new state of the client
         */
        void setClientState(ClientState state);

    private:
        b12software::network::HostInfos _host; /*!< The host of the client */
        std::string _username; /*!< The username of the client */
        ClientState _state; /*!< The internal state of the client */
    };
}

#endif //R_TYPE_CLIENT_HPP
