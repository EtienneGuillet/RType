/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _TEXT_COMPONENT_HPP_
#define _TEXT_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

namespace rtype {

    class TextComponent : public ecs::IComponent {

        public:
        static const ecs::Version Version;

        TextComponent(const int fontId, const std::string &string = "");

        ~TextComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;

        const ecs::Version &getVersion() const override;

        const std::string &getString() const;

        void setString(const std::string &string);

        const sf::Font &getFont() const;

        void setFont(const sf::Font &font);

        const sf::Text &getText() const;

        bool isFontSet() const;

        int getFontId() const;

        void setText(const sf::Text &text);

        private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Text _text;
        bool _fontIsSet;
        std::string _string;
        int _fontId;
    };
}

#endif // _TEXT_COMPONENT_HPP_
