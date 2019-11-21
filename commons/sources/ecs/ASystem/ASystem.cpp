#include "ecs/ASystem/ASystem.hpp"

ecs::ASystem::ASystem()
: _isRunning(false)
{
}

bool ecs::ASystem::isRunning() const
{
    return _isRunning;
}

void ecs::ASystem::start()
{
    _isRunning = true;
}

void ecs::ASystem::stop()
{
    _isRunning = false;
}

void ecs::ASystem::setWorld(const std::weak_ptr<IWorld> &world)
{
    _world = world;
}
