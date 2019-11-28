/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** EntityInfos.cpp
*/

/* Created the 27/11/2019 at 14:04 by julian.frabel@epitech.eu */

#include "EntityInfos.hpp"

rtype::EntityInfos::EntityInfos(bool hasDisplay, bool hasHp)
    : _hasDisplay(hasDisplay)
    , _hasHp(hasHp)
    , _posX(0)
    , _posY(0)
    , _posZ(0)
    , _rotX(0)
    , _rotY(0)
    , _scaleX(1)
    , _scaleY(1)
    , _type(0)
    , _hp(0)
    , _id(0)
{

}

rtype::EntityInfos::~EntityInfos()
{

}

rtype::EntityInfos::EntityInfos(const rtype::EntityInfos &other)
    : _hasDisplay(static_cast<bool>(other._hasDisplay))
    , _hasHp(static_cast<bool>(other._hasHp))
    , _posX(static_cast<uint32_t>(other._posX))
    , _posY(static_cast<uint32_t>(other._posY))
    , _posZ(static_cast<uint32_t>(other._posZ))
    , _rotX(static_cast<uint32_t>(other._rotX))
    , _rotY(static_cast<uint32_t>(other._rotY))
    , _scaleX(static_cast<uint32_t>(other._scaleX))
    , _scaleY(static_cast<uint32_t>(other._scaleY))
    , _type(static_cast<uint32_t>(other._type))
    , _hp(static_cast<uint32_t>(other._hp))
    , _id(static_cast<uint64_t>(other._id))
{

}

rtype::EntityInfos &rtype::EntityInfos::operator=(const rtype::EntityInfos &rhs)
{
    if (&rhs == this)
        return *this;
    _hasDisplay = static_cast<bool>(rhs._hasDisplay);
    _hasHp = static_cast<bool>(rhs._hasHp);
    _posX = static_cast<uint32_t>(rhs._posX);
    _posY = static_cast<uint32_t>(rhs._posY);
    _posZ = static_cast<uint32_t>(rhs._posZ);
    _rotX = static_cast<uint32_t>(rhs._rotX);
    _rotY = static_cast<uint32_t>(rhs._rotY);
    _scaleX = static_cast<uint32_t>(rhs._scaleX);
    _scaleY = static_cast<uint32_t>(rhs._scaleY);
    _type = static_cast<uint32_t>(rhs._type);
    _hp = static_cast<uint32_t>(rhs._hp);
    _id = static_cast<uint64_t>(rhs._id);
    return *this;
}

b12software::maths::Vector3D rtype::EntityInfos::getPosition() const
{
    return b12software::maths::Vector3D(_posX, _posY, _posZ);
}

void rtype::EntityInfos::setPosition(const b12software::maths::Vector3D &position)
{
    _posX = position.x;
    _posY = position.y;
    _posZ = position.z;
}

void rtype::EntityInfos::setPosition(int x, int y, int z)
{
    _posX = x;
    _posY = y;
    _posZ = z;
}

b12software::maths::Vector2D rtype::EntityInfos::getRotation() const
{
    return b12software::maths::Vector2D(_rotX, _rotY);
}

void rtype::EntityInfos::setRotation(const b12software::maths::Vector2D &rotation)
{
    _rotX = rotation.x;
    _rotY = rotation.y;
}

void rtype::EntityInfos::setRotation(int x, int y)
{
    _rotX = x;
    _rotY = y;
}

b12software::maths::Vector2D rtype::EntityInfos::getScale() const
{
    return b12software::maths::Vector2D(_scaleX, _scaleY);
}

void rtype::EntityInfos::setScale(const b12software::maths::Vector2D &scale)
{
    _scaleX = scale.x;
    _scaleY = scale.y;
}

void rtype::EntityInfos::setScale(int x, int y)
{
    _scaleX = x;
    _scaleY = y;
}

uint32_t rtype::EntityInfos::getType() const
{
    return _type;
}

void rtype::EntityInfos::setType(uint32_t type)
{
    _type = type;
}

uint32_t rtype::EntityInfos::getHp() const
{
    return _hp;
}

void rtype::EntityInfos::setHp(uint32_t hp)
{
    _hp = hp;
}

uint32_t rtype::EntityInfos::getId() const
{
    return _id;
}

void rtype::EntityInfos::setId(uint32_t id)
{
    _id = id;
}
