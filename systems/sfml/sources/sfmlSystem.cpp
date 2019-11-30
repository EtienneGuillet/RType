#include "sfmlSystem.hpp"
#include "exception/SfmlSystemException.hpp"
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/RectangleShapeComponent.hpp>
#include "components/GameManager/GameManagerComponent.hpp"

const ecs::Version SfmlSystem::Version = ecs::Version("System_Sfml", 0, 1, 0, 0);

SfmlSystem::SfmlSystem()
    : _mouseInput()
    , _inputs()
    , _clock()
    , _window()
    , _fonts()
    , _textures()
    , _started(false)
{
}

void SfmlSystem::start()
{
    if (_started)
        return;
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
    _started = true;
}

void SfmlSystem::loadTextures()
{
    std::string filename = "r-typesheet";
    std::string extension = ".gif";

    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    for (int i = 0; i < NBR_TEXTURE; i++) {
        _textures[i].first = std::make_shared<sf::Texture>();
        std::string path;
        path.append(PATH_TO_ASSETS);
        path.append(filename);
        path.append(std::to_string(i + 1));
        path.append(extension);
        if (!_textures[i].first->loadFromFile(path)) {
            throw SfmlSystemException("Texture didn't load, file " + path + " not found.", WHERE);
        }
        std::map<int, sf::IntRect> mapRectTexture = getMapRectTexture();
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
        _fonts[i] = std::make_shared<sf::Font>();
        std::string path;
        path.append(PATH_TO_FONTS);
        path.append(filename);
        path.append(std::to_string(i + 1));
        path.append(extension);
        if (!_fonts[i]->loadFromFile(path)) {
            throw SfmlSystemException("Font didn't load, file " + path + " not found.", WHERE);
        }
    }
}

void SfmlSystem::stop()
{
    if (!_started)
        return;
    auto lockedWorld = _world.lock();
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "Stop");
    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::SpriteComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components.front().lock());
            spriteComponent->invalidateSprite();
        });
        lockedWorld->applyToEach({rtype::TextComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components.front().lock());
            textComponent->invalidateText();
        });
    }

    _fonts.clear();
    _textures.clear();
    _window.close();
    _started = false;
}

bool SfmlSystem::isHovering(const sf::Text &text)
{
    float left = text.getGlobalBounds().left;
    float width = text.getGlobalBounds().left + text.getGlobalBounds().width;
    float top = text.getGlobalBounds().top + text.getGlobalBounds().height;
    float height = text.getGlobalBounds().top + text.getGlobalBounds().height + text.getGlobalBounds().height;

    return left < sf::Mouse::getPosition().x &&
        width > sf::Mouse::getPosition().x &&
        top < sf::Mouse::getPosition().y &&
        height > sf::Mouse::getPosition().y;
}

void SfmlSystem::manageMouseEvents([[maybe_unused]]sf::Event event)
{
    auto lockedWorld = _world.lock();

    _mouseInput.first = sf::Mouse::getPosition().x;
    _mouseInput.second = sf::Mouse::getPosition().y;
    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::TextComponent::Version, rtype::TransformComponent::Version, rtype::HoverComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components[0].lock());
            std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());
            std::shared_ptr<rtype::HoverComponent> hoverComponent = std::dynamic_pointer_cast<rtype::HoverComponent>(components[2].lock());

            if (textComponent && transformComponent && hoverComponent) {
                if (textComponent->isTextSet() && hoverComponent->getHoverable()) {
                    if (isHovering(textComponent->getText())) {
                        textComponent->setColorText(sf::Color::Red);
                        textComponent->setOutlineColorText(sf::Color::White);
                    } else {
                        textComponent->setColorText(sf::Color::White);
                        textComponent->setOutlineColorText(sf::Color::Red);
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                        isHovering(textComponent->getText())) {
                        const auto &func = hoverComponent->getFunctionPointer();
                        if (func) {
                            func();
                        }
                    }
                }
            }
        });
    }
}

void SfmlSystem::manageKeyboardEvents(sf::Event event)
{
    auto lockedWorld = _world.lock();

    if (lockedWorld) {
        lockedWorld->applyToEach({rtype::TextComponent::Version, rtype::TransformComponent::Version, rtype::UpdateTextComponent::Version}, [this, &event] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
            std::shared_ptr<rtype::TextComponent> textComponent = std::dynamic_pointer_cast<rtype::TextComponent>(components[0].lock());
            auto text = textComponent->getText();
            auto string = text.getString().toAnsiString();

            if ((event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= '0' && event.text.unicode <= '9')) {
                text.setString(string + static_cast<char>(event.text.unicode));
                textComponent->setText(text);
            } else if (event.text.unicode == 8) {
                if (string.size() > 5) {
                    string.erase(string.size() - 1, string.size());
                    textComponent->setString(string);
                }
            }
        });
    }
}

void SfmlSystem::tick([[maybe_unused]]long deltatime)
{
    sf::Event event;

    try {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                auto lockedWorld = _world.lock();
                if (lockedWorld) {
                    lockedWorld->applyToEach({rtype::GameManagerComponent::Version}, []([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
                        auto gm = std::dynamic_pointer_cast<rtype::GameManagerComponent>(components[0].lock());
                        if (gm) {
                            gm->getShouldClose() = true;
                        }
                    });
                }
                break;
            }
            this->manageMouseEvents(event);
            if (event.type == sf::Event::TextEntered) {
                this->manageKeyboardEvents(event);
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
    lockedWorld->applyToEach({rtype::SpriteComponent::Version, rtype::TransformComponent::Version, rtype::ScrollComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components[0].lock());
        std::shared_ptr<rtype::ScrollComponent> scrollComponent = std::dynamic_pointer_cast<rtype::ScrollComponent>(components[2].lock());
        if (spriteComponent && scrollComponent) {
            if (spriteComponent->isSpriteSetted()) {
                sf::IntRect rect = spriteComponent->getSprite().getTextureRect();
                rect.left += scrollComponent->getScrollValues().x;
                rect.top += scrollComponent->getScrollValues().y;
                spriteComponent->getSprite().setTextureRect(rect);
            }
        }
    });
    lockedWorld->applyToEach({rtype::SpriteComponent::Version, rtype::TransformComponent::Version}, [this] ([[maybe_unused]]std::weak_ptr<ecs::IEntity> entity, std::vector<std::weak_ptr<ecs::IComponent>> components) {
        std::shared_ptr<rtype::SpriteComponent> spriteComponent = std::dynamic_pointer_cast<rtype::SpriteComponent>(components.front().lock());
        std::shared_ptr<rtype::TransformComponent> transformComponent = std::dynamic_pointer_cast<rtype::TransformComponent>(components[1].lock());

        if (!spriteComponent->isSpriteSetted()) {
            sf::Sprite sprite;
            auto it = _textures.find(spriteComponent->getAssetId() - 1);
            if (it == _textures.end())
                return;
            if (spriteComponent->isRepeated()) {
                it->second.first->setRepeated(true);
            }
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
            textComponent->setColorText(sf::Color::White);
            textComponent->setOutlineColorText(sf::Color::Red);
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
