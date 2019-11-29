/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** LobbyState.cpp
*/

/* Created the 29/11/2019 at 15:47 by julian.frabel@epitech.eu */

#include <algorithm>
#include "LobbyState.hpp"

const rtype::LobbyState::LobbyData rtype::LobbyState::emptyLobby = {"", "", false, -1, -1};

rtype::LobbyState::LobbyState()
    : _username("")
    , _inLobby(false)
    , _requestLobbyList(false)
    , _createLobby(false)
    , _failedToCreateLobbyError("")
    , _joinLobby(false)
    , _failedToJoinLobbyError("")
    , _quitLobby(false)
    , _failedToQuitLobbyError("")
    , _lobbyList()
    , _currentLobby(emptyLobby)
    , _playersName()
{

}

rtype::LobbyState::~LobbyState()
{

}

rtype::LobbyState::LobbyState(const rtype::LobbyState &other)
    : _username(other._username)
    , _inLobby(other._inLobby)
    , _requestLobbyList(other._requestLobbyList)
    , _createLobby(other._createLobby)
    , _failedToCreateLobbyError(other._failedToCreateLobbyError)
    , _joinLobby(other._joinLobby)
    , _failedToJoinLobbyError(other._failedToJoinLobbyError)
    , _quitLobby(other._quitLobby)
    , _failedToQuitLobbyError(other._failedToQuitLobbyError)
    , _lobbyList(other._lobbyList)
    , _currentLobby(other._currentLobby)
    , _playersName(other._playersName)
{

}

rtype::LobbyState &rtype::LobbyState::operator=(const rtype::LobbyState &other)
{
    if (&other == this)
        return *this;
    _username = other._username;
    _inLobby = other._inLobby;
    _requestLobbyList = other._requestLobbyList;
    _createLobby = other._createLobby;
    _failedToCreateLobbyError = other._failedToCreateLobbyError;
    _joinLobby = other._joinLobby;
    _failedToJoinLobbyError = other._failedToJoinLobbyError;
    _quitLobby = other._quitLobby;
    _failedToQuitLobbyError = other._failedToQuitLobbyError;
    _lobbyList = other._lobbyList;
    _currentLobby = other._currentLobby;
    _playersName = other._playersName;
    return *this;
}

bool rtype::LobbyState::isInLobby() const
{
    return _inLobby;
}

const rtype::LobbyState::LobbyData &rtype::LobbyState::getCurrentLobbyData() const
{
    return _currentLobby;
}

const std::vector<std::string> &rtype::LobbyState::getPlayersInLobby() const
{
    return _playersName;
}

bool rtype::LobbyState::isUpdatingLobby() const
{
    return _requestLobbyList;
}

void rtype::LobbyState::requestLobbyListUpdate()
{
    _requestLobbyList = true;
}

const std::vector<rtype::LobbyState::LobbyData> &rtype::LobbyState::getLobbyList() const
{
    return _lobbyList;
}

bool rtype::LobbyState::isCreatingLobby() const
{
    return _createLobby;
}

void rtype::LobbyState::createLobby(const std::string &name, const std::string &password, int maxSize)
{
    if (_joinLobby || _inLobby || _quitLobby || _createLobby) {
        _failedToJoinLobbyError = "You are currently already in a lobby / joining a lobby / creating a lobby / quitting a lobby";
        return;
    }
    _inLobby= false;
    _quitLobby = false;
    _createLobby = false;
    _joinLobby = true;
    _failedToJoinLobbyError.clear();
    _currentLobby.name = name;
    _currentLobby.password = password;
    _currentLobby.hasPassword = !password.empty();
    _currentLobby.size = maxSize;
    _currentLobby.nbPlayers = 1;
    _playersName.clear();
}

bool rtype::LobbyState::hasFailToCreateLobby() const
{
    return !_failedToCreateLobbyError.empty();
}

const std::string &rtype::LobbyState::failToJoinLobbyError() const
{
    return _failedToCreateLobbyError;
}

bool rtype::LobbyState::isJoiningLobby() const
{
    return _joinLobby;
}

void rtype::LobbyState::joinLobby(const std::string &name, const std::string &password)
{
    if (_joinLobby || _inLobby || _quitLobby || _createLobby) {
        _failedToJoinLobbyError = "You are currently already in a lobby / joining a lobby / creating a lobby / quitting a lobby";
        return;
    }
    auto lobbyIt = std::find_if(_lobbyList.begin(), _lobbyList.end(), [&name](const LobbyData &elem) {
        return elem.name == name;
    });
    if (lobbyIt == _lobbyList.end()) {
        _failedToJoinLobbyError = "Lobby not found";
        return;
    }
    _inLobby= false;
    _quitLobby = false;
    _createLobby = false;
    _joinLobby = true;
    _failedToJoinLobbyError.clear();
    _currentLobby.name = name;
    _currentLobby.password = password;
    _currentLobby.hasPassword = !password.empty();
    _currentLobby.size = lobbyIt->size;
    _currentLobby.nbPlayers = lobbyIt->size + 1;
    _playersName.clear();
}

bool rtype::LobbyState::hasFailToJoinLobby() const
{
    return !_failedToJoinLobbyError.empty();
}

const std::string &rtype::LobbyState::failToCreateLobbyError() const
{
    return _failedToJoinLobbyError;
}

bool rtype::LobbyState::isQuittingLobby() const
{
    return _quitLobby;
}

void rtype::LobbyState::quitLobby()
{
    _quitLobby = true;
}

bool rtype::LobbyState::hasFailToQuitLobby() const
{
    return !_failedToQuitLobbyError.empty();
}

const std::string &rtype::LobbyState::failToQuitLobbyError() const
{
    return _failedToQuitLobbyError;
}

void rtype::LobbyState::validateCreate()
{
    _createLobby = false;
    _inLobby = true;
    _playersName.clear();
    _playersName.push_back(_username);
    _currentLobby.nbPlayers = 1;
}

void rtype::LobbyState::validateJoin(const std::vector<std::string> &names)
{
    _joinLobby = false;
    _inLobby = true;
    _playersName = names;
    _currentLobby.nbPlayers = names.size();
}

void rtype::LobbyState::validateQuit()
{
    _inLobby = false;
    _quitLobby = false;
}

void rtype::LobbyState::addToLobby(const std::string &name)
{
    _playersName.push_back(name);
    _currentLobby.nbPlayers = _playersName.size();
}

void rtype::LobbyState::removeFromLobby(const std::string &name)
{
    auto playerName = std::find(_playersName.begin(), _playersName.end(), name);
    if (playerName == _playersName.end())
        return;
    _playersName.erase(playerName);
    _currentLobby.nbPlayers = _playersName.size();
}

void rtype::LobbyState::setAvailableLobby(const std::vector<LobbyData> &lobbys)
{
    _lobbyList = lobbys;
}

void rtype::LobbyState::invalidateCreate(const std::string &error)
{
    _createLobby = false;
    _failedToCreateLobbyError = error;
}

void rtype::LobbyState::invalidateJoin(const std::string &error)
{
    _joinLobby = false;
    _failedToJoinLobbyError = error;
}

void rtype::LobbyState::invalidateQuit(const std::string &error)
{
    _quitLobby = false;
    _failedToQuitLobbyError = error;
}

const std::string &rtype::LobbyState::getUsername() const
{
    return _username;
}

void rtype::LobbyState::setUsername(const std::string &username)
{
    _username = username;
}
