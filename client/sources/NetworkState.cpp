/*
** EPITECH PROJECT, 2022
** NetworkState.cpp
** File description:
** Created by tpautier,
*/

#include "NetworkState.hpp"
#include "exception/GameStateException.hpp"

void rtype::NetworkState::addEntity(const rtype::EntitiesState &entity)
{
    _entities.push_back(entity);
}

void rtype::NetworkState::removeEntity(std::uint32_t id)
{
    for (auto it = _entities.begin(); it != _entities.end(); ++it) {
        if (it->getId() != id)
            continue;
        _entities.erase(it);
        return;
    }
}

rtype::EntitiesState& rtype::NetworkState::getEntity(std::uint32_t id)
{
    for (unsigned long int i = 0; i < _entities.size(); i++) {
        if (_entities[i].getId() != id)
            continue;
        return _entities[i];
    }
    throw GameStateException("The id invalid.", WHERE);
}

std::vector<rtype::EntitiesState>& rtype::NetworkState::getEntities()
{
    
    return _entities;
}

std::vector<rtype::EntitiesState> rtype::NetworkState::getEntities(const std::vector<std::uint32_t> &ids)
{
    std::vector<rtype::EntitiesState> vector;

    for (auto & entity : _entities) {
        for (unsigned int id : ids) {
            if (entity.getId() == id)
                vector.push_back(entity);
        }
    }
    return vector;
}

bool rtype::NetworkState::comparePositionZ(rtype::EntitiesState entity1, rtype::EntitiesState entity2)
{
    return (entity1.getPos().z < entity2.getPos().z);
}

void rtype::NetworkState::sortByZindex()
{
    std::sort(_entities.begin(), _entities.end(), comparePositionZ);
}

void rtype::NetworkState::setInputs(const std::map<Keys, bool> &keys)
{
    _inputs = keys;
}

const std::map<Keys, bool>& rtype::NetworkState::getInputs()
{
    return _inputs;
}

void rtype::NetworkState::setInput(Keys key, bool state)
{
    _inputs[key] = state;
}

void rtype::NetworkState::setCharge(uint8_t charge)
{
    _charge = charge;
}

uint8_t rtype::NetworkState::getCharge() const
{
    return _charge;
}

rtype::LobbyState &rtype::NetworkState::getLobbyState()
{
    return _lobbyState;
}

const std::string &rtype::NetworkState::getServerHost() const
{
    return _serverHost;
}

void rtype::NetworkState::setServerHost(const std::string &serverHost)
{
    if (_serverHost != serverHost)
        _serverInfoChanged = true;
    _serverHost = serverHost;
}


unsigned short rtype::NetworkState::getServerPort() const
{
    return _serverPort;
}

void rtype::NetworkState::setServerPort(unsigned short serverPort)
{
    if (_serverPort != serverPort)
        _serverInfoChanged = true;
    _serverPort = serverPort;
}

bool rtype::NetworkState::hasServerInfoChanged()
{
    auto ret = _serverInfoChanged;
    _serverInfoChanged = false;
    return ret;
}

bool rtype::NetworkState::isTryingToConnected() const
{
    return _tryToConnect;
}

void rtype::NetworkState::connect(const std::string &username)
{
    if (_tryToConnect || _isConnected) {
        _connectionErrorMessage = "You are already connected / trying to connected";
        return;
    }
    _tryToConnect = true;
    _connectionErrorMessage.clear();
    _lobbyState.setUsername(username);
}

bool rtype::NetworkState::isConnnected() const
{
    return _isConnected;
}

bool rtype::NetworkState::failedToConnect() const
{
    return !_connectionErrorMessage.empty();
}

const std::string &rtype::NetworkState::getConnectionErrorMessage() const
{
    return _connectionErrorMessage;
}

void rtype::NetworkState::setConnectionStatus(bool isSuccess, const std::string &errorMessage)
{
    _isConnected = isSuccess;
    _tryToConnect = false;
    _connectionErrorMessage = errorMessage;
    _lostConnection = isSuccess;
}

bool rtype::NetworkState::hasLostConnection() const
{
    return _lostConnection;
}

void rtype::NetworkState::setLostConnection(bool value)
{
    _lostConnection = value;
}

const std::tuple<int, int, int, int> &rtype::NetworkState::getScores() const
{
    return _scores;
}

void rtype::NetworkState::setScores(const std::tuple<int, int, int, int> &scores)
{
    _scores = scores;
}

bool rtype::NetworkState::isInGame() const
{
    return _inGame;
}

void rtype::NetworkState::setInGame(bool inGame)
{
    _inGame = inGame;
}

bool rtype::NetworkState::isPlayAgain() const
{
    return _playAgain;
}

void rtype::NetworkState::setPlayAgain(bool playAgain)
{
    _playAgain = playAgain;
}
