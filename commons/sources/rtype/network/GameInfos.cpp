/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** GameInfos.cpp
*/

/* Created the 27/11/2019 at 13:46 by julian.frabel@epitech.eu */

#include "GameInfos.hpp"

rtype::GameInfos::GameInfos()
    : enable_shared_from_this<GameInfos>()
    , _nbPlayers(4)
    , _players()
    , _entities()
{

}

rtype::GameInfos::~GameInfos()
{

}

int rtype::GameInfos::getNbPlayers() const
{
    return _nbPlayers;
}

void rtype::GameInfos::setNbPlayers(int nbPlayer)
{
    _nbPlayers = nbPlayer;
}

rtype::PlayerInfos &rtype::GameInfos::getPlayer(int nb)
{
    if (nb < 0)
        return _players[0];
    if (nb >= 4)
        return _players[3];
    return _players[nb];
}

const rtype::PlayerInfos &rtype::GameInfos::getPlayer(int nb) const
{
    if (nb < 0)
        return _players[0];
    if (nb >= 4)
        return _players[3];
    return _players[nb];
}

void rtype::GameInfos::setPlayer(int nb, const rtype::PlayerInfos &infos)
{
    if (nb < 0)
        _players[0] = infos;
    if (nb >= 4)
        _players[3] = infos;
    _players[nb] = infos;
}

b12software::containers::ThreadSafeList<rtype::EntityInfos> &rtype::GameInfos::getEntities()
{
    return _entities;
}

const b12software::containers::ThreadSafeList<rtype::EntityInfos> &rtype::GameInfos::getEntities() const
{
    return _entities;
}

void rtype::GameInfos::setEntities(const b12software::containers::ThreadSafeList<rtype::EntityInfos> &entities)
{
    _entities = entities;
}

void rtype::GameInfos::addEntity(const rtype::EntityInfos &entity)
{
    _entities.push_back(entity);
}

void rtype::GameInfos::removeEntity(uint32_t id)
{
    _entities.remove_if([id](const EntityInfos &info) {
        return info.getId() == id;
    });
}

void rtype::GameInfos::removeEntity(const rtype::EntityInfos &entity)
{
    auto id = entity.getId();
    _entities.remove_if([id](const EntityInfos &info) {
        return info.getId() == id;
    });
}

void rtype::GameInfos::removeEntities(const std::function<bool(const rtype::EntityInfos &)> &func)
{
    _entities.remove_if(func);
}

rtype::GameInfos::GameInfos(const rtype::GameInfos &other)
    : enable_shared_from_this<GameInfos>(other)
    , _nbPlayers(static_cast<int>(other._nbPlayers))
    , _players()
    , _entities(other._entities)
{
    _players[0] = other._players[0];
    _players[1] = other._players[1];
    _players[2] = other._players[2];
    _players[3] = other._players[3];
}

rtype::GameInfos &rtype::GameInfos::operator=(const rtype::GameInfos &rhs)
{
    if (&rhs == this)
        return *this;
    _nbPlayers = static_cast<int>(rhs._nbPlayers);
    _players[0] = rhs._players[0];
    _players[1] = rhs._players[1];
    _players[2] = rhs._players[2];
    _players[3] = rhs._players[3];
    _entities = rhs._entities;
    return *this;
}

void rtype::GameInfos::reset()
{
    _nbPlayers = 0;
    auto emptyPlayer = PlayerInfos();
    _players[0] = emptyPlayer;
    _players[1] = emptyPlayer;
    _players[2] = emptyPlayer;
    _players[3] = emptyPlayer;
    _entities.clear();
}

std::weak_ptr<rtype::GameInfos> rtype::GameInfos::getWeak()
{
    return weak_from_this();
}
