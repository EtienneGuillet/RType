/*
** EPITECH PROJECT, 2022
** SpriteComponent.cpp
** File description:
** Created by tpautier,
*/

#include "SpriteComponent.hpp"

const ecs::Version rtype::SpriteComponent::Version = ecs::Version("SpriteComponent", 0, 0, 0, 1);

rtype::SpriteComponent::SpriteComponent(const int assetId) :_isRepeat(false), _isSpriteSet(false), _assetId(assetId)
{
}

void rtype::SpriteComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
{
    _entity = entity;
}

const ecs::Version &rtype::SpriteComponent::getVersion() const
{
    return SpriteComponent::Version;
}

bool rtype::SpriteComponent::isRepeated() const
{
    return _isRepeat;
}

void rtype::SpriteComponent::setRepeated(const bool isRepeat)
{
    sf::Texture texture = (*_sprite->getTexture());
    texture.setRepeated(isRepeat);
    _sprite->setTexture(texture);
    _isRepeat = isRepeat;
}

const sf::IntRect &rtype::SpriteComponent::getTextureRect() const
{
    return _sprite->getTextureRect();
}

void rtype::SpriteComponent::setTextureRect(const sf::IntRect &rect)
{
    _sprite->setTextureRect(rect);
}

sf::Sprite &rtype::SpriteComponent::getSprite()
{
    return *_sprite;
}

void rtype::SpriteComponent::setSprite(const sf::Sprite &sprite)
{
    _sprite = std::make_unique<sf::Sprite>(sprite);
    _isSpriteSet = true;
}

int rtype::SpriteComponent::getAssetId() const
{
    return _assetId;
}

void rtype::SpriteComponent::invalidateSprite()
{
    _isSpriteSet = false;
    _sprite = std::unique_ptr<sf::Sprite>();
}

bool rtype::SpriteComponent::isSpriteSetted() const
{
    return _isSpriteSet;
}
