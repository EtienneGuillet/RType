/*
** EPITECH PROJECT, 2022
** sfmlSystem.cpp
** File description:
** Created by tpautier,
*/

#include "sfmlSystem.hpp"

const ecs::Version SfmlSystem::Version = ecs::Version("SfmlSystem", 0, 1, 0, 0);

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
    this->loadTextures();
}

void SfmlSystem::loadTextures()
{
    std::string filename = "r-typesheet";
    std::string extension = ".gif";

    for (int i = 1; i < NBR_TEXTURE; i++) {
        sf::Texture texture;
        std::string path;
        path.append(filename);
        path.append(std::to_string(i));
        path.append(extension);
        texture.loadFromFile(path);
        _textures[i] = std::make_shared<sf::Texture>(texture);
    }
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
            _mouseInput.first = sf::Mouse::getPosition().x;
            _mouseInput.second = sf::Mouse::getPosition().y;
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
    this->renderEntities();
}

void SfmlSystem::renderEntities()
{
    _window.clear(sf::Color::Black);
    auto lockedWorld = _world.lock();
    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::SpriteComponent::Version}, [this] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components.front().lock());

            _window.draw(spriteComponent->getSprite());
        });
    }

    _window.display();
}

bool SfmlSystem::isRunning() const
{
    return _window.isOpen();
}

const ecs::Version& SfmlSystem::getType() const
{
    return Version;
}