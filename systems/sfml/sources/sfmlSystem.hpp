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
#include "components/RectangleShapeComponent.hpp"
#include "components/CircleShapeComponent.hpp"
#include "components/ConvexShapeComponent.hpp"
#include <SFML/Window.hpp>
#include <map>
#include <logger/DefaultLogger.hpp>
#include <SFML/Graphics.hpp>

#define PATH_TO_ASSETS "./bin/assets/"
#define PATH_TO_FONTS "./bin/fonts/"
#define NBR_TEXTURE 42
#define NBR_FONT 2

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

    static std::map<int, sf::IntRect> getMapRectTexture()
    {
        std::map<int, sf::IntRect> map;
        map[42] = sf::Rect(66,0,33,17);
        return map;
    }

    /*
     * @brief Used to load all textures from /bin/assets.
     */
    void loadTextures();

    /*
     * @brief Used to load all fonts /bin/fonts.
     */
    void loadFonts();

    /*
     * @brief Render all entities on the screen that has a spriteComponent, a RectangleComponent, a CircleComponent or a ConvexComponent.
     */
    void renderEntities();

    static const ecs::Version Version;
    std::pair</*x*/float, /*y*/float> _mouseInput;
    std::map<Keys, bool> _inputs;
    sf::Clock _clock;
    sf::RenderWindow _window;
    std::map<int, std::shared_ptr<sf::Font>> _fonts;
    std::map<int, std::pair<std::shared_ptr<sf::Texture>, sf::IntRect>> _textures;
};

#endif //R_TYPE_SFMLSYSTEM_HPP
