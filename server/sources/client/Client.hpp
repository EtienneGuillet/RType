/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Client.hpp
*/

/* Created the 22/11/2019 at 18:21 by julian.frabel@epitech.eu */

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP

#include <chrono>
#include <map>
#include "rtype/network/RTypeDatagramType.hpp"
#include "rtype/network/RTypeDatagram.hpp"
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
        using Clock = std::chrono::high_resolution_clock;
        using Duration = Clock::duration;
        using TimePoint = Clock::time_point;
        static constexpr TimePoint epoch = TimePoint();
        static const rtype::network::RTypeDatagram defaultDg;

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

        /*!
         * @brief Equality operator
         * @param rhs The client to compare to
         * @return true if host and username are the same false otherwise
         */
        bool operator==(const Client &rhs) const;
        /*!
         * @brief Inequality operator
         * @param rhs The client to compare to
         * @return false if host and username are the same true otherwise
         */
        bool operator!=(const Client &rhs) const;

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

        /*!
         * @brief get the last time_point this client was reached
         * @return the last time point this client was reached
         */
        const TimePoint &getLastReached() const;
        /*!
         * @brief Set the time point for this client
         * @param lastReached the new time point to set
         */
        void setLastReached(const TimePoint &lastReached);

        /*!
         * @brief get the clock for this client for a datagram type
         * @param type the type of datagram
         * @return the last time point for this datagram type (epoch if none)
         */
        const TimePoint &getClock(rtype::network::RTypeDatagramType type) const;
        /*!
         * @brief Set the time point clock for this datagram type
         * @param type the type of datagram
         * @param clock the new time point to set
         */
        void setClock(rtype::network::RTypeDatagramType type, const TimePoint &clock);

        /*!
         * @brief Get a datagram for a type
         * @param type the type of datagram
         * @return The datagram if exist an invalid datagram else
         */
        const rtype::network::RTypeDatagram &getDatagram(rtype::network::RTypeDatagramType type) const;
        /*!
         * @brief Set a datagram for a type
         * @param type The type of datagram to set
         * @param datagram The datagram to send
         */
        void setDatagram(rtype::network::RTypeDatagramType type, const rtype::network::RTypeDatagram &datagram);

    private:
        b12software::network::HostInfos _host; /*!< The host of the client */
        std::string _username; /*!< The username of the client */
        ClientState _state; /*!< The internal state of the client */
        TimePoint _lastReached; /*!< The last time this client was reached */
        std::map<rtype::network::RTypeDatagramType, TimePoint> _clocks; /*!< Internal clocks for this client */
        std::map<rtype::network::RTypeDatagramType, rtype::network::RTypeDatagram> _datagrams; /*!< The datagrams to send unless a response is received*/
    };
}

#endif //R_TYPE_CLIENT_HPP
