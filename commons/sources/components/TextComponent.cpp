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

    TextComponent::TextComponent(const int fontId, const std::string &string)
        : _textIsSet(false), _string(string), _fontId(fontId)
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

    const sf::Text &TextComponent::getText() const
    {
        return _text;
    }

    void TextComponent::setText(const sf::Text &text)
    {
        _text = text;
    }

    bool TextComponent::isTextSet() const
    {
        return _textIsSet;
    }

    int TextComponent::getFontId() const
    {
        return _fontId;
    }
}

