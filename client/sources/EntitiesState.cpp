#include "EntitiesState.hpp"

rtype::EntitiesState::EntitiesState()
: _id(0), _type(0), _posX(0), _posY(0), _posZ(0), _rotX(0), _rotY(0), _scaleX(1), _scaleY(1)
{
}

void rtype::EntitiesState::setPos(int x, int y, int z)
{
    _posX = x;
    _posY = y;
    _posZ = z;
}

const std::map<std::string, int>& rtype::EntitiesState::getPos() const
{
    std::map<std::string, int> map;

    map["x"] = _posX;
    map["y"] = _posY;
    map["z"] = _posZ;
    return map;
}