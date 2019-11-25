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

    TextComponent::TextComponent(const std::string &text, const sf::Font &font)
        : _text(text), _font(font)
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(
            b12software::logger::LogLevelDebug, "test TextComponent");
    }

    TextComponent::TextComponent(const std::string &text,
        const std::string &fontPath
    ) : _text(text)
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(
            b12software::logger::LogLevelDebug, "test TextComponent");

        sf::Font font;
        font.loadFromFile(fontPath);
        _font = font;
    }

    void TextComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &TextComponent::getVersion() const
    {
        return TextComponent::Version;
    }

    const std::string &TextComponent::getText() const
    {
        return _text;
    }

    void TextComponent::setString(const std::string &text)
    {
        _text = text;
    }

    const sf::Font &TextComponent::getFont() const
    {
        return _font;
    }

    void TextComponent::setFont(const sf::Font &font)
    {
        _font = font;
    }

    void TextComponent::setFontFromFile(const std::string &fontPath)
    {
        _font.loadFromFile(fontPath);
    }
}