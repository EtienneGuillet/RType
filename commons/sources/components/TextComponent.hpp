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

        TextComponent(const std::string &text, const sf::Font &font);

        TextComponent(const std::string &text, const std::string &fontPath);

        ~TextComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;

        const ecs::Version &getVersion() const override;

        const std::string &getText() const;

        void setString(const std::string &text);

        const sf::Font &getFont() const;

        void setFont(const sf::Font &font);

        void setFontFromFile(const std::string &font);

        private:
        std::weak_ptr<ecs::IEntity> _entity;
        std::string _text;
        sf::Font _font;
    };
}

#endif // _TEXT_COMPONENT_HPP_
