/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Room.cpp
*/

/* Created the 26/11/2019 at 05:12 by julian.frabel@epitech.eu */

#include <algorithm>
#include "Room.hpp"

rtype::Room::Room()
    : _name(),
      _capacity(),
      _slotUsed(),
      _hasPassword(),
      _password(),
      _gameRunning(),
      _clients()
{

}

rtype::Room::~Room()
{

}

const std::string &rtype::Room::getName() const
{
    return _name;
}

void rtype::Room::setName(const std::string &name)
{
    _name = name;
}

unsigned char rtype::Room::getCapacity() const
{
    return _capacity;
}

void rtype::Room::setCapacity(unsigned char capacity)
{
    _capacity = capacity;
}

unsigned char rtype::Room::getSlotUsed() const
{
    return _slotUsed;
}

void rtype::Room::setSlotUsed(unsigned char slotUsed)
{
    _slotUsed = slotUsed;
}

bool rtype::Room::hasPassword() const
{
    return _hasPassword;
}

void rtype::Room::setHasPassword(bool hasPassword)
{
    _hasPassword = hasPassword;
}

const std::string &rtype::Room::getPassword() const
{
    return _password;
}

void rtype::Room::setPassword(const std::string &password)
{
    _password = password;
}

bool rtype::Room::isGameRunning() const
{
    return _gameRunning;
}

void rtype::Room::setGameRunning(bool gameRunning)
{
    _gameRunning = gameRunning;
}

void rtype::Room::addClient(rtype::Client &client)
{
    auto it = std::find(_clients.begin(), _clients.end(), client);
    if (it == _clients.end()) {
        _clients.push_back(client);
        _slotUsed++;
    }
}

void rtype::Room::removeClient(const rtype::Client &client)
{
    auto it = _clients.begin();
    while (it != _clients.end()) {
        auto next = it + 1;
        if (*it == client) {
            _clients.erase(it);
            _slotUsed--;
        }
        it = next;
    }
}

void rtype::Room::applyToClients(std::function<void(Client & )> func)
{
    for (auto &client : _clients) {
        func(client);
    }
}
