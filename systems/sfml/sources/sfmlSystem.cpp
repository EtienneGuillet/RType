/*
** EPITECH PROJECT, 2022
** sfmlSystem.cpp
** File description:
** Created by tpautier,
*/

#include "sfmlSystem.hpp"

void SfmlSystem::start()
{
    _window.create(sf::VideoMode(800, 600, 32), "R_Type", sf::Style::Fullscreen);
    _window.setFramerateLimit(60);
}

void SfmlSystem::stop()
{
    _window.close();
}

void SfmlSystem::tick(long deltatime)
{
}

bool SfmlSystem::isRunning() const
{
    if (_window.isOpen())
        return true;
    else
        return false;
}

const ecs::Version& SfmlSystem::getType() const
{
    ecs::Version version("SfmlSystem", 0,1,0,0);

    return 
}