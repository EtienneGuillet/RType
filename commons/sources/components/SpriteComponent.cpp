/*
** EPITECH PROJECT, 2022
** SpriteComponent.cpp
** File description:
** Created by tpautier,
*/

#include "SpriteComponent.hpp"

namespace rtype {

    const ecs::Version SpriteComponent::Version = ecs::Version("SpriteComponent", 0, 0, 0, 1);

    SpriteComponent::SpriteComponent(const int assetId)
        :_isRepeat(false), _isSpriteSet(false), _assetId(assetId)
    {
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
        _isSpriteSet = true;
    }

    int SpriteComponent::getAssetId() const
    {
        return _assetId;
    }

    bool SpriteComponent::isSpriteSetted() const
    {
        return _isSpriteSet;
    }
} /* rtype */
