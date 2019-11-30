/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PlayerInfos.cpp
*/

/* Created the 27/11/2019 at 14:06 by julian.frabel@epitech.eu */

#include "PlayerInfos.hpp"

rtype::PlayerInfos::PlayerInfos()
    : EntityInfos(true, true)
    , _used(false)
    , _shooting(false)
    , _movingUp(false)
    , _movingDown(false)
    , _movingLeft(false)
    , _movingRight(false)
    , _charge(0)
    , _score(0)
{

}

rtype::PlayerInfos::~PlayerInfos()
{

}

rtype::PlayerInfos::PlayerInfos(const rtype::PlayerInfos &other)
    : EntityInfos(other)
    , _used(static_cast<bool>(other._used))
    , _shooting(static_cast<bool>(other._shooting))
    , _movingUp(static_cast<bool>(other._movingUp))
    , _movingDown(static_cast<bool>(other._movingDown))
    , _movingLeft(static_cast<bool>(other._movingLeft))
    , _movingRight(static_cast<bool>(other._movingRight))
    , _charge(static_cast<char>(other._charge))
    , _score(static_cast<uint32_t>(other._score))
{

}

rtype::PlayerInfos &rtype::PlayerInfos::operator=(const rtype::PlayerInfos &rhs)
{
    if (&rhs == this)
        return *this;
    EntityInfos::operator=(rhs);
    _shooting = static_cast<bool>(rhs._shooting);
    _movingUp = static_cast<bool>(rhs._movingUp);
    _movingDown = static_cast<bool>(rhs._movingDown);
    _movingLeft = static_cast<bool>(rhs._movingLeft);
    _movingRight = static_cast<bool>(rhs._movingRight);
    _charge = static_cast<char>(rhs._charge);
    _score = static_cast<uint32_t>(rhs._score);
    _used = static_cast<bool>(rhs._used);
    return *this;
}

bool rtype::PlayerInfos::isUsed() const
{
    return _used;
}

void rtype::PlayerInfos::setIsUsed(bool used)
{
    _used = used;
}

bool rtype::PlayerInfos::isShooting() const
{
    return _shooting;
}

void rtype::PlayerInfos::setIsShooting(bool shooting)
{
    _shooting = shooting;
}

bool rtype::PlayerInfos::isMovingUp() const
{
    return _movingUp;
}

void rtype::PlayerInfos::setIsMovingUp(bool movingUp)
{
    _movingUp = movingUp;
}

bool rtype::PlayerInfos::isMovingDown() const
{
    return _movingDown;
}

void rtype::PlayerInfos::setIsMovingDown(bool movingDown)
{
    _movingDown = movingDown;
}

bool rtype::PlayerInfos::isMovingLeft() const
{
    return _movingLeft;
}

void rtype::PlayerInfos::setIsMovingLeft(bool movingLeft)
{
    _movingLeft = movingLeft;
}

bool rtype::PlayerInfos::isMovingRight() const
{
    return _movingRight;
}

void rtype::PlayerInfos::setIsMovingRight(bool movingRight)
{
    _movingRight = movingRight;
}

char rtype::PlayerInfos::getCharge() const
{
    return _charge;
}

void rtype::PlayerInfos::setCharge(char charge)
{
    _charge = charge;
}

uint32_t rtype::PlayerInfos::getScore() const
{
    return _score;
}

void rtype::PlayerInfos::setScore(uint32_t score)
{
    _score = score;
}
