#include "sfmlSystem.hpp"
#include "exception/SfmlSystemException.hpp"
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/RectangleShapeComponent.hpp>

const ecs::Version SfmlSystem::Version = ecs::Version("System_Sfml", 0, 1, 0, 0);

void SfmlSystem::start()
{
    try {
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
        this->loadFonts();
    } catch (SfmlSystemException &e) {
        std::cerr << e.what() << e.where() << std::endl;
    }
}

void SfmlSystem::loadTextures()
{
    std::string filename = "r-typesheet";
    std::string extension = ".gif";

    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    for (int i = 0; i < NBR_TEXTURE; i++) {
        sf::Texture texture;
        std::string path;
        path.append(PATH_TO_ASSETS);
        path.append(filename);
        path.append(std::to_string(i + 1));
        path.append(extension);
        if (!texture.loadFromFile(path)) {
            throw SfmlSystemException("Texture didn't load, file " + path + " not found.", WHERE);
        }
        _textures[i] = std::make_shared<sf::Texture>(texture);
    }
}

void SfmlSystem::loadFonts()
{
    std::string filename = "r-typeFont";
    std::string extension = ".ttf";

    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
    for (int i = 0; i < NBR_FONT; i++) {
        sf::Font font;
        std::string path;
        path.append(PATH_TO_FONTS);
        path.append(filename);
        path.append(std::to_string(i + 1));
        path.append(extension);
        if (!font.loadFromFile(path)) {
            throw SfmlSystemException("Font didn't load, file " + path + " not found.", WHERE);
        }
        _fonts[i] = std::make_shared<sf::Font>(font);
    }
}

void SfmlSystem::stop()
{
    _window.close();
}

void SfmlSystem::tick(long deltatime)
{
    sf::Event event;
    (void)deltatime;

    try {
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
    } catch (SfmlSystemException &e) {
        std::cerr << e.what() << e.where() << std::endl;
    }
}

void SfmlSystem::renderEntities()
{
    _window.clear(sf::Color::Black);
    auto lockedWorld = _world.lock();
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));
    if (lockedWorld) {
        //render the Sprites.
        lockedWorld->applyToEach({rtype::SpriteComponent::Version}, [this] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components.front().lock());
            (void)entity;
            if (!spriteComponent->isSpriteSetted()) {
                sf::Sprite sprite;
                auto it = _textures.find(spriteComponent->getAssetId() - 1);
                if (it == _textures.end())
                    return;
                sprite.setTexture(*(it->second));
                spriteComponent->setSprite(sprite);
            }
            _window.draw(spriteComponent->getSprite());
        });
        //render the Texts.
        lockedWorld->applyToEach({rtype::TextComponent::Version}, [this] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components.front().lock());
            (void)entity;
            if (!textComponent->isTextSet()) {
                sf::Text text;
                auto it = _fonts.find(textComponent->getFontId() - 1);
                if (it == _fonts.end())
                    return;
                text.setString(textComponent->getString());
                text.setFont(*(_fonts[textComponent->getFontId()]));
                textComponent->setText(text);
            }
            _window.draw(textComponent->getText());
        });
        //render the Rectangle.
        lockedWorld->applyToEach({rtype::RectangleShapeComponent::Version}, [this] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::RectangleShapeComponent> rectangleComponent = std::dynamic_pointer_cast<rtype::RectangleShapeComponent>(components.front().lock());
            (void)entity;
            _window.draw(rectangleComponent->getShape());
        });
        //render the Circles.
        lockedWorld->applyToEach({rtype::CircleShapeComponent::Version}, [this] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::CircleShapeComponent> circleComponent = std::dynamic_pointer_cast<rtype::CircleShapeComponent>(components.front().lock());
            (void)entity;
            _window.draw(circleComponent->getShape());
        });
        //render the Convexs.
        lockedWorld->applyToEach({rtype::RectangleShapeComponent::Version}, [this] (std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::RectangleShapeComponent> rectangleComponent = std::dynamic_pointer_cast<rtype::RectangleShapeComponent>(components.front().lock());
            (void)entity;
            _window.draw(rectangleComponent->getShape());
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