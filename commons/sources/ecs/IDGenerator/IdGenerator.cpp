/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** IdGenerator.cpp
*/

/* Created the 19/11/2019 at 21:02 by julian.frabel@epitech.eu */

#include "IdGenerator.hpp"

ecs::IDGenerator::IDGenerator()
    : _maxID(0), _freeIds()
{

}

ecs::IDGenerator::IDGenerator(const ecs::IDGenerator &other)
    : _maxID(other._maxID), _freeIds(other._freeIds)
{

}

ecs::IDGenerator &ecs::IDGenerator::operator=(const ecs::IDGenerator &rhs)
{
    if (&rhs == this)
        return *this;
    _maxID = rhs._maxID;
    _freeIds = rhs._freeIds;
    return *this;
}

int ecs::IDGenerator::generateNewID()
{
    if (!_freeIds.empty()) {
        int id = _freeIds.front();
        _freeIds.pop();
        return id;
    }
    _maxID++;
    return _maxID;
}

void ecs::IDGenerator::freeId(int id)
{
    _freeIds.push(id);
}
