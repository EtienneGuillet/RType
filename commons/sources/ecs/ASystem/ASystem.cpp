#include "ASystem.hpp"

ASystem::ASystem()
{
    this.isRunning = false;
}

bool ASystem::isRunning()
{
    return this.isRunning;
}

void ASystem::start()
{
    this.isRunning = true;
}

void ASystem::stop()
{
    this.isRunning = false;
}
