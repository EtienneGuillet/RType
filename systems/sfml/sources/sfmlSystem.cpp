#include "sfmlSystem.hpp"
#include "exception/SfmlSystemException.hpp"
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/RectangleShapeComponent.hpp>

const ecs::Version SfmlSystem::Version = ecs::Version("System_Sfml", 0, 1, 0, 0);

void SfmlSystem::start()
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Start");
    try {
        _inputs[Z] = false;
        _inputs[Q] = false;
        _inputs[S] = false;
        _inputs[D] = false;
        _inputs[SPACE] = false;
        _inputs[ESCAPE] = false;
        _inputs[ENTER] = false;
        _window.create(sf::VideoMode(1920, 1080, 32), "R-Type");
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
        std::map<int, sf::IntRect> mapRectTexture = getMapRectTexture();
        _textures[i].first = std::make_shared<sf::Texture>(texture);
        auto it = mapRectTexture.find(i + 1);
        if (it != mapRectTexture.end()) {
            _textures[i].second = mapRectTexture[i + 1];
        } else {
            _textures[i].second = sf::IntRect(-1, -1, -1, -1);
        }
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
    auto lockedWorld = _world.lock();

    lockedWorld->applyToEach({rtype::SpriteComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components.front().lock());
        spriteComponent->invalidateSprite();
    });
    lockedWorld->applyToEach({rtype::TextComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components.front().lock());
        textComponent->invalidateText();
    });
    _window.close();
}

void SfmlSystem::manageMouseEvents(sf::Event event)
{
    auto lockedWorld = _world.lock();

    event = event;
    _mouseInput.first = sf::Mouse::getPosition().x;
    _mouseInput.second = sf::Mouse::getPosition().y;
    lockedWorld->applyToEach({rtype::TextComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components.front().lock());
        //todo la hitbox du composant text correspond à la souris
        if (true) {
            textComponent->setOutlineColorText(sf::Color::White);
            textComponent->setColorText(sf::Color::Red);
        }
        else {
            textComponent->setOutlineColorText(sf::Color::Red);
            textComponent->setColorText(sf::Color::White);
        }
    });
}

void SfmlSystem::tick([[maybe_unused]]long deltatime)
{
    sf::Event event;

    try {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop();
                break;
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
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z) {
                _inputs[Z] = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) {
                _inputs[Q] = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
                _inputs[S] = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
                _inputs[D] = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                _inputs[SPACE] = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                _inputs[ESCAPE] = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
                _inputs[ENTER] = false;
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
        this->renderSprites(lockedWorld);
        this->renderShapes(lockedWorld);
        this->renderTexts(lockedWorld);
    }
    _window.display();
}

void SfmlSystem::renderSprites(const std::shared_ptr<ecs::IWorld> &lockedWorld)
{
    lockedWorld->applyToEach({rtype::SpriteComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components.front().lock());
        std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());

        if (!spriteComponent->isSpriteSetted()) {
            sf::Sprite sprite;
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Entity detected");
            auto it = _textures.find(spriteComponent->getAssetId() - 1);
            if (it == _textures.end())
                return;
            sprite.setTexture(*(it->second.first), true);
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Sprite set");
            if (it->second.second != sf::IntRect(-1, -1, -1, -1)) {
                b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Set texture rect");
                sprite.setTextureRect(it->second.second);
            }
            spriteComponent->setSprite(sprite);
        }
        spriteComponent->getSprite().setRotation(transformComponent->getRotation().y);
        spriteComponent->getSprite().setScale(transformComponent->getScale());
        spriteComponent->getSprite().setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
        _window.draw(spriteComponent->getSprite());
    });
}

void SfmlSystem::renderTexts(const std::shared_ptr<ecs::IWorld> &lockedWorld)
{
    lockedWorld->applyToEach({rtype::TextComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components.front().lock());
        std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());

        if (!textComponent->isTextSet()) {
            sf::Text text;
            auto it = _fonts.find(textComponent->getFontId() - 1);
            if (it == _fonts.end())
                return;
            text.setString(textComponent->getString());
            text.setFont(*(_fonts[textComponent->getFontId()]));
            textComponent->setText(text);
        }
        textComponent->getText().setRotation(transformComponent->getRotation().y);
        textComponent->getText().setScale(transformComponent->getScale());
        textComponent->getText().setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
        _window.draw(textComponent->getText());
    });
}

void SfmlSystem::renderShapes(const std::shared_ptr<ecs::IWorld> &lockedWorld)
{
    //render the Rectangle.
    lockedWorld->applyToEach({rtype::RectangleShapeComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::RectangleShapeComponent> rectangleComponent = std::dynamic_pointer_cast<rtype::RectangleShapeComponent>(components.front().lock());
        std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());

        rectangleComponent->getShape().setRotation(transformComponent->getRotation().y);
        rectangleComponent->getShape().setScale(transformComponent->getScale());
        rectangleComponent->getShape().setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
        _window.draw(rectangleComponent->getShape());
    });
    //render the Circles.
    lockedWorld->applyToEach({rtype::CircleShapeComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::CircleShapeComponent> circleComponent = std::dynamic_pointer_cast<rtype::CircleShapeComponent>(components.front().lock());
        std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());

        circleComponent->getShape().setRotation(transformComponent->getRotation().y);
        circleComponent->getShape().setScale(transformComponent->getScale());
        circleComponent->getShape().setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
        _window.draw(circleComponent->getShape());
    });
    //render the Convexs.
    lockedWorld->applyToEach({rtype::ConvexShapeComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::ConvexShapeComponent> convexComponent = std::dynamic_pointer_cast<rtype::ConvexShapeComponent>(components.front().lock());
        std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());

        convexComponent->getShape().setRotation(transformComponent->getRotation().y);
        convexComponent->getShape().setScale(transformComponent->getScale());
        convexComponent->getShape().setPosition(transformComponent->getPosition().x, transformComponent->getPosition().y);
        _window.draw(convexComponent->getShape());
    });
}

bool SfmlSystem::isRunning() const
{
    return _window.isOpen();
}

const ecs::Version& SfmlSystem::getType() const
{
    return Version;
}
