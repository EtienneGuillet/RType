/*
** EPITECH PROJECT, 2022
** TextComponent.cpp
** File description:
** Created by tpautier,
*/

#include "TextComponent.hpp"

namespace rtype {

    const ecs::Version TextComponent::Version = ecs::Version("TextComponent", 0,
        0, 0, 1);

    TextComponent::TextComponent(const int assetId, const std::string &string)
        : _fontIsSet(false), _string(string), _assetId(assetId)
    {
    }

    void TextComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &TextComponent::getVersion() const
    {
        return TextComponent::Version;
    }

    const std::string &TextComponent::getString() const
    {
        return _string;
    }

    void TextComponent::setString(const std::string &string)
    {
        _string = string;
        _text.setString(_string);
    }

    const sf::Font &TextComponent::getFont() const
    {
        return (*_text.getFont());
    }

    void TextComponent::setFont(const sf::Font &font)
    {
        _text.setFont(font);
        _fontIsSet = true;
    }

    const sf::Text &TextComponent::getText() const
    {
        return _text;
    }

    void TextComponent::setText(const sf::Text &text)
    {
        _text = text;
    }
}
