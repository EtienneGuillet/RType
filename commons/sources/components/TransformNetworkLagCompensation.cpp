/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** TransformNetworkLagCompensation.cpp
*/

/* Created the 01/12/2019 at 17:47 by julian.frabel@epitech.eu */

#include "TransformNetworkLagCompensation.hpp"

const ecs::Version rtype::TransformNetworkLagCompensation::Version = ecs::Version("TransformNetworkLagCompensation", 0, 0, 1, 0);

rtype::TransformNetworkLagCompensation::TransformNetworkLagCompensation()
    : _hasEnougthValues(0)
    , _lastNetworkPos()
    , _previousNetworkPos()
    , _lastTP()
    , _previousTP()
    , _elapsed(0)
    , _dir()
{

}

const ecs::Version &rtype::TransformNetworkLagCompensation::getVersion() const
{
    return Version;
}

void rtype::TransformNetworkLagCompensation::setLastNetworkPos(const b12software::maths::Vector3D &pos)
{
    _previousNetworkPos = _lastNetworkPos;
    _lastNetworkPos = pos;
    _previousTP = _lastTP;
    _lastTP = std::chrono::high_resolution_clock::now();
    if (_hasEnougthValues < 2) {
        _hasEnougthValues++;
    } else {
        _elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_lastTP - _previousTP);
        _dir = (_lastNetworkPos - _previousNetworkPos);
        auto divisor = _elapsed.count() / 1000.0f;
        _dir.x /= divisor;
        _dir.y /= divisor;
        _dir.z /= divisor;
    }
}

const b12software::maths::Vector3D &rtype::TransformNetworkLagCompensation::getLastNetworkPos() const
{
    return _lastNetworkPos;
}

const std::chrono::high_resolution_clock::time_point &rtype::TransformNetworkLagCompensation::getLastUpdate() const
{
    return _lastTP;
}

const b12software::maths::Vector3D &rtype::TransformNetworkLagCompensation::getDirection() const
{
    return _dir;
}

const b12software::maths::Vector3D &rtype::TransformNetworkLagCompensation::getPreviousNetworkPos() const
{
    return _previousNetworkPos;
}

const std::chrono::high_resolution_clock::time_point &rtype::TransformNetworkLagCompensation::getPreviousUpdate() const
{
    return _previousTP;
}

const std::chrono::milliseconds &rtype::TransformNetworkLagCompensation::getElapsed() const
{
    return _elapsed;
}
