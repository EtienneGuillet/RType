/*
** EPITECH PROJECT, 2022
** ShapeComponent.cpp
** File description:
** Created by tpautier,
*/

#include "ShapeComponent.hpp"

namespace rtype {

    const ecs::Version ShapeComponent::Version = ecs::Version("ShapeComponent", 0, 0, 0, 1);

    ShapeComponent::ShapeComponent(const std::string &text, const sf::Font &font)
        :_text(text), _font(font)
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test ShapeComponent");
    }

    ShapeComponent::ShapeComponent(const std::string &text, const std::string &fontPath)
        :_text(text)
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test ShapeComponent");

        sf::Font font;
        font.loadFromFile(fontPath);
        _font = font;
    }

    void ShapeComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &ShapeComponent::getVersion() const
    {
        return ShapeComponent::Version;
    }
} /* rtype */
