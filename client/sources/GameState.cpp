/*
** EPITECH PROJECT, 2022
** GameState.cpp
** File description:
** Created by tpautier,
*/

#include "GameState.hpp"
#include "exception/GameStateException.hpp"

void rtype::GameState::addEntity(const rtype::EntitiesState &entity)
{
    _entities.push_back(entity);
}

void rtype::GameState::removeEntity(std::uint32_t id)
{
    for (auto it = _entities.begin(); it != _entities.end(); ++it) {
        if (it->getId() != id)
            continue;
        _entities.erase(it);
        return;
    }
}

const rtype::EntitiesState& rtype::GameState::getEntity(std::uint32_t id) const
{
    for (unsigned long int i = 0; i < _entities.size(); i++) {
        if (_entities[i].getId() != id)
            continue;
        return _entities[i];
    }
    throw GameStateException("The id invalid.", WHERE);
}

const std::vector<rtype::EntitiesState>& rtype::GameState::getEntities() const
{
    
    return _entities;
}

std::vector<rtype::EntitiesState> rtype::GameState::getEntities(const std::vector<std::uint32_t> &ids)
{
    std::vector<rtype::EntitiesState> vector;

    for (unsigned long int i = 0; i < _entities.size(); i++) {
        for (unsigned long int j = 0; j < ids.size(); j++) {
            if (_entities[i].getId() == ids[j])
                vector.push_back(_entities[i]);
        }
    }
    return vector;
}

void rtype::GameState::setInputs(const std::map<Keys, bool> &keys)
{
    _inputs = keys;
}

const std::map<Keys, bool>& rtype::GameState::getInputs()
{
    return _inputs;
}