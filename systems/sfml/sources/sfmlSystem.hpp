/*
** EPITECH PROJECT, 2022
** sfmlSystem.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_SFMLSYSTEM_HPP
#define R_TYPE_SFMLSYSTEM_HPP

#include "ecs/ASystem/ASystem.hpp"
#include <SFML/Window.hpp>

class SfmlSystem : public ecs::ASystem {

    public:
    SfmlSystem() = default;
    ~SfmlSystem() override = default;

    void start() override;
    void stop() override;
    void tick(long deltatime) override;
    bool isRunning() const override;
    const ecs::Version &getType() const override;

    private:

    sf::Clock _clock;
    sf::Window _window;
};

#endif //R_TYPE_SFMLSYSTEM_HPP
