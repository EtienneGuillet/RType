/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Client.cpp
*/

/* Created the 22/11/2019 at 18:21 by julian.frabel@epitech.eu */

#include "Client.hpp"

rtype::Client::Client()
    : _host(b12software::network::emptyHost), _username(), _state(CS_IN_LOBBY)
{

}

rtype::Client::Client(const b12software::network::HostInfos &host, const std::string &username,
                      rtype::ClientState state)
    : _host(host), _username(username), _state(state)
{

}


void rtype::Client::setHost(const b12software::network::HostInfos &host)
{
    _host = host;
}

const b12software::network::HostInfos &rtype::Client::getHost() const
{
    return _host;
}

const std::string &rtype::Client::getUsername() const
{
    return _username;
}

void rtype::Client::setUsername(const std::string &username)
{
    _username = username;
}
rtype::ClientState rtype::Client::getClientState() const
{
    return _state;
}

void rtype::Client::setClientState(rtype::ClientState state)
{
    _state = state;
}
