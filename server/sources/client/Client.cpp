/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Client.cpp
*/

/* Created the 22/11/2019 at 18:21 by julian.frabel@epitech.eu */

#include "Client.hpp"

const rtype::network::RTypeDatagram rtype::Client::defaultDg = rtype::network::RTypeDatagram();

rtype::Client::Client()
    : _host(b12software::network::emptyHost), _username(), _state(CS_IN_LOBBY), _lastReached(Clock::now()), _clocks(), _datagrams(), _room()
{

}

rtype::Client::Client(const b12software::network::HostInfos &host, const std::string &username,
                      rtype::ClientState state)
    : _host(host), _username(username), _state(state), _lastReached(Clock::now()), _clocks(), _datagrams(), _room()
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

const rtype::Client::TimePoint &rtype::Client::getLastReached() const
{
    return _lastReached;
}

void rtype::Client::setLastReached(const rtype::Client::TimePoint &lastReached)
{
    _lastReached = lastReached;
}

const rtype::Client::TimePoint &rtype::Client::getClock(rtype::network::RTypeDatagramType type) const
{
    auto clock = _clocks.find(type);
    if (clock == _clocks.end()) {
        return epoch;
    }
    return clock->second;
}

void rtype::Client::setClock(rtype::network::RTypeDatagramType type, const rtype::Client::TimePoint &clock)
{
    _clocks[type] = clock;
}

bool rtype::Client::operator==(const rtype::Client &rhs) const
{
    return _host == rhs._host && _username == rhs._username;
}

bool rtype::Client::operator!=(const rtype::Client &rhs) const
{
    return !(rhs == *this);
}

const rtype::network::RTypeDatagram &rtype::Client::getDatagram(rtype::network::RTypeDatagramType type) const
{
    auto datagram = _datagrams.find(type);
    if (datagram != _datagrams.end()) {
        return datagram->second;
    }
    return defaultDg;
}

void rtype::Client::setDatagram(rtype::network::RTypeDatagramType type, const rtype::network::RTypeDatagram &datagram)
{
    _datagrams[type] = datagram;
}

std::vector<rtype::network::RTypeDatagramType> rtype::Client::getDatagramTypes() const
{
    std::vector<rtype::network::RTypeDatagramType> ret;
    for (auto &pair : _datagrams) {
        if (pair.second.isValid()) {
            ret.push_back(pair.first);
        }
    }
    return ret;
}

const std::weak_ptr<rtype::Room> &rtype::Client::getRoom() const
{
    return _room;
}

void rtype::Client::setRoom(const std::weak_ptr<rtype::Room> &room)
{
    _room = room;
}

void rtype::Client::removeRoom()
{
    _room = std::weak_ptr<rtype::Room>();
}