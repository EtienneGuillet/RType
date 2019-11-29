#include "EntitiesState.hpp"

rtype::EntitiesState::EntitiesState()
: _id(0), _type(0), _posX(0), _posY(0), _posZ(0), _rotX(0), _rotY(0), _scaleX(1), _scaleY(1)
{
}

void rtype::EntitiesState::setPos(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    _posX = x;
    _posY = y;
    _posZ = z;
}

b12software::maths::Vector3D rtype::EntitiesState::getPos() const
{
    b12software::maths::Vector3D vector3D(_posX, _posY, _posZ);
    return vector3D;
}

void rtype::EntitiesState::setRot(std::uint32_t x, std::uint32_t y)
{
    _rotX = x;
    _rotY = y;
}

b12software::maths::Vector2D rtype::EntitiesState::getRot() const
{
    b12software::maths::Vector2D vector2D(_rotX, _rotY);
    return vector2D;
}

void rtype::EntitiesState::setScale(std::uint32_t x, std::uint32_t y)
{
    _scaleX = x;
    _scaleY = y;
}

b12software::maths::Vector2D rtype::EntitiesState::getScale() const
{
    b12software::maths::Vector2D vector2D(_scaleX, _scaleY);
    return vector2D;
}

void rtype::EntitiesState::setId(std::uint32_t id)
{
    _id = id;
}

std::uint32_t rtype::EntitiesState::getId() const
{
    return _id;
}

void rtype::EntitiesState::setType(std::uint32_t type)
{
    _type = type;
}

std::uint32_t rtype::EntitiesState::getType() const
{
    return _type;
}

const std::chrono::high_resolution_clock::time_point &rtype::EntitiesState::getLastDisplayUpdate() const
{
    return _lastDisplayUpdate;
}

void rtype::EntitiesState::setLastDisplayUpdate(const std::chrono::high_resolution_clock::time_point &lastDisplayUpdate)
{
    _lastDisplayUpdate = lastDisplayUpdate;
}

const std::chrono::high_resolution_clock::time_point &rtype::EntitiesState::getLastUpdate() const
{
    return _lastUpdate;
}

void rtype::EntitiesState::setLastUpdate(const std::chrono::high_resolution_clock::time_point &lastUpdate)
{
    _lastUpdate = lastUpdate;
}
