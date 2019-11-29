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
        _text->setString(_string);
    }

    sf::Text &TextComponent::getText()
    {
        return *_text;
    }

    void TextComponent::setText(const sf::Text &text)
    {
        _textIsSet = true;
        _text = std::make_unique<sf::Text>(text);
    }

    bool TextComponent::isTextSet() const
    {
        return _textIsSet;
    }

    void TextComponent::invalidateText()
    {
        _text = std::unique_ptr<sf::Text>();
        _textIsSet = false;
    }

    int TextComponent::getFontId() const
    {
        return _fontId;
    }

    void TextComponent::setColorText(const sf::Color &color)
    {
        if (_text)
            _text->setFillColor(color);
    }

    void TextComponent::setOutlineColorText(const sf::Color &color)
    {
        if (_text) {
            _text->setOutlineThickness(3);
            _text->setOutlineColor(color);
        }
    }
}
