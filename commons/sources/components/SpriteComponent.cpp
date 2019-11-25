/*
** EPITECH PROJECT, 2022
** SpriteComponent.cpp
** File description:
** Created by tpautier,
*/

#include "SpriteComponent.hpp"

namespace rtype {

    const ecs::Version SpriteComponent::Version = ecs::Version("SpriteComponent", 0, 0, 0, 1);

    SpriteComponent::SpriteComponent(const sf::Texture &texture)
        :_isRepeat(false)
    {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test SpriteComponent");

        sf::Sprite sprite;

        sprite.setTexture(texture);
        _sprite = sprite;
    }

    SpriteComponent::SpriteComponent(const sf::Sprite &sprite)
        :_sprite(sprite), _isRepeat(false)
    {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test SpriteComponent");
    }

    SpriteComponent::SpriteComponent(const std::string &fontPath, const bool isRepeat, const sf::IntRect &rect)
        :_isRepeat(isRepeat)
    {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test SpriteComponent");

        sf::Texture texture;

        texture.loadFromFile(fontPath, rect);
        if (isRepeat)
            texture.setRepeated(isRepeat);

        sf::Sprite sprite(texture);

        _sprite = sprite;
    }

    void SpriteComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &SpriteComponent::getVersion() const
    {
        return SpriteComponent::Version;
    }

    bool SpriteComponent::isRepeated() const
    {
        return _isRepeat;
    }

    void SpriteComponent::setRepeated(const bool isRepeat)
    {
        sf::Texture texture = (*_sprite.getTexture());
        texture.setRepeated(isRepeat);
        _sprite.setTexture(texture);
        _isRepeat = isRepeat;
    }

    const sf::IntRect &SpriteComponent::getTextureRect() const
    {
        return _sprite.getTextureRect();
    }

    void SpriteComponent::setTextureRect(const sf::IntRect &rect)
    {
        _sprite.setTextureRect(rect);
    }

    const sf::Sprite &SpriteComponent::getSprite() const
    {
        return _sprite;
    }

    void SpriteComponent::setSprite(const sf::Sprite &sprite)
    {
        _sprite = sprite;
    }

    const sf::Texture &SpriteComponent::getTexture() const
    {
        return (*_sprite.getTexture());
    }

    void SpriteComponent::setTexture(const sf::Texture &texture)
    {
        _sprite.setTexture(texture);
    }
} /* rtype */
