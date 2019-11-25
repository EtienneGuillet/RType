/*
** EPITECH PROJECT, 2022
** sfmlSystem.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_SFMLSYSTEM_HPP
#define R_TYPE_SFMLSYSTEM_HPP

#include "ecs/ASystem/ASystem.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/TransformComponent.hpp"
#include <SFML/Window.hpp>
#include <map>
#include <logger/DefaultLogger.hpp>
#include <SFML/Graphics.hpp>

#define NBR_TEXTURE 42

enum Keys {
    Z,
    Q,
    S,
    D,
    SPACE,
    ESCAPE,
    ENTER
};

class SfmlSystem : public ecs::ASystem {

    public:

    /*
     * @brief Ctor.
     */
    SfmlSystem() = default;

    /*
     * @brief Ctor.
     */
    ~SfmlSystem() override = default;

    /*
     * @brief Start a new window. Call loadTextures method.
     */
    void start() override;

    /*
     * @brief Stop the window.
     */
    void stop() override;

    /*
     * @brief Check for potential Inputs, such as mouse click, or game related inputs.
     * Also call renderEntities method.
     * @param deltatime time elapsed since the last call.
     */
    void tick(long deltatime) override;

    /*
     * @brief Check if the window is opened.
     * @return true if the window is open, false otherwise.
     */
    bool isRunning() const override;

    /*
     * @brief Inform the type of the system.
     * @return The type of the system.
     */
    const ecs::Version &getType() const override;

    private:

    void loadTextures();
    void renderEntities();

    static const ecs::Version Version;
    std::pair</*x*/float, /*y*/float> _mouseInput;
    std::map<Keys, bool> _inputs;
    sf::Clock _clock;
    sf::RenderWindow _window;
    std::map<int, std::shared_ptr<sf::Texture>> _textures;
};

#endif //R_TYPE_SFMLSYSTEM_HPP
