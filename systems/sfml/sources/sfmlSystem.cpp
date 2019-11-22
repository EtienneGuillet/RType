/*
** EPITECH PROJECT, 2022
** sfmlSystem.cpp
** File description:
** Created by tpautier,
*/

#include "sfmlSystem.hpp"

void SfmlSystem::start()
{
    _inputs[Z] = false;
    _inputs[Q] = false;
    _inputs[S] = false;
    _inputs[D] = false;
    _inputs[SPACE] = false;
    _inputs[ESCAPE] = false;
    _inputs[ENTER] = false;
    _window.create(sf::VideoMode(800, 600, 32), "R-Type");
    _window.setFramerateLimit(60);
}

void SfmlSystem::stop()
{
    _window.close();
}

void SfmlSystem::tick(long deltatime)
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            stop();
            break;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
            _inputs[Z] = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
            _inputs[Q] = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
            _inputs[S] = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
            _inputs[D] = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            _inputs[SPACE] = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _inputs[ESCAPE] = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            _inputs[ENTER] = true;
        }
    }
}

bool SfmlSystem::isRunning() const
{
    return _window.isOpen();
}

const ecs::Version& SfmlSystem::getType() const
{
    ecs::Version version("SfmlSystem", 0,1,0,0);

    return version;
}