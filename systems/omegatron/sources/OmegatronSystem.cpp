#include "OmegatronSystem.hpp"

const ecs::Version OmegatronSystem::Version = ecs::Version("System_Omegatron", 0, 1, 0, 0);


OmegatronSystem::OmegatronSystem() :
_isRunning(false)
{
}

void OmegatronSystem::start()
{
    _isRunning = true;
}

void OmegatronSystem::stop()
{
    _isRunning = false;
}

void OmegatronSystem::tick(long deltatime)
{
    if (!_isRunning)
        return;

}

const ecs::Version& OmegatronSystem::getType() const
{
    return Version;
}