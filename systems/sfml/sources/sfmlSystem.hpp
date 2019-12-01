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
#include "components/HoverComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/RectangleShapeComponent.hpp"
#include "components/CircleShapeComponent.hpp"
#include "components/ScrollComponent.hpp"
#include "components/ConvexShapeComponent.hpp"
#include "components/UpdateTextComponent.hpp"
#include <SFML/Window.hpp>
#include <map>
#include <logger/DefaultLogger.hpp>
#include <SFML/Graphics.hpp>
#include "rtype/client/NetworkState.hpp"

#define PATH_TO_ASSETS "./bin/assets/"
#define PATH_TO_FONTS "./bin/fonts/"
#define NBR_TEXTURE 53
#define NBR_FONT 2

class SfmlSystem : public ecs::ASystem {

    public:

    static const ecs::Version Version;

    /*
     * @brief Ctor.
     */
    SfmlSystem();

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
     * @brief try to connect the client to the server.
     */
    void tryForConnection();

    /*
     * @brief check if the client is trying to create a room.
     */
    void checkCreateRoom();

    /*
     * @brief Inform the type of the system.
     * @return The type of the system.
     */
    const ecs::Version &getType() const override;

    private:

    static std::map<int, sf::IntRect> getMapRectTexture()
    {
        std::map<int, sf::IntRect> map;
        map[8] = sf::Rect(0, 34, 34, 34);
        map[47] = sf::Rect(66, 0, 33, 17);
        map[48] = sf::Rect(66, 0, 33, 17);
        map[49] = sf::Rect(66, 0, 33, 17);
        map[50] = sf::Rect(66, 0, 33, 17);
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
     * @brief Used to manage the mouse on the sfml window.
     */
    void manageMouseEvents(sf::Event event);

    void manageKeyboardEvents(sf::Event event);

    /*
     * @brief Lock the world and call every rendering methods.
     */
    void renderEntities();

    /*
     * @brief Render all entities on the screen that has a spriteComponent and a transformComponent.
     */
    void renderSprites(const std::shared_ptr<ecs::IWorld> &lockedWorld);

    /*
     * @brief Render all entities on the screen that has a textComponent and a transformComponent.
     */
    void renderTexts(const std::shared_ptr<ecs::IWorld> &lockedWorld);

    /*
     * @brief Render all entities on the screen that has a transformComponent and a circleComponent, a rectangleComponent or a ConvexComponent.
     */
    void renderShapes(const std::shared_ptr<ecs::IWorld> &lockedWorld);

    bool isHovering(const sf::Text &text);

    std::weak_ptr<rtype::NetworkState> _networkState;
    std::pair</*x*/float, /*y*/float> _mouseInput;
    std::map<NetworkStateKeys, bool> _inputs;
    sf::Clock _clock;
    sf::RenderWindow _window;
    std::map<int, std::shared_ptr<sf::Font>> _fonts;
    std::map<int, std::pair<std::shared_ptr<sf::Texture>, sf::IntRect>> _textures;
    bool _started;
    bool _portSet;
    bool _addrSet;
    bool _roomNameSet;
    bool _roomPswSet;
    std::string _roomName;
    std::string _roomPsw;
    bool _connected;
};

#endif //R_TYPE_SFMLSYSTEM_HPP
