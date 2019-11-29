/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _TEXT_COMPONENT_HPP_
#define _TEXT_COMPONENT_HPP_

#include "ecs/IComponent/AComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class TextComponent
     * @brief This class is a component allowing to display a text.
     */
    class TextComponent : public ecs::AComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param fontId Id of the font used to display the text.
         */
        TextComponent(const int fontId, const std::string &string = "");

        /*!
         * @brief Dtor.
         */
        ~TextComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;

        const ecs::Version &getVersion() const override;

        /*!
         * @brief Return the string of the text.
         */
        const std::string &getString() const;

        /*!
         * @brief Set the string of the text.
         * @param string content of the text
         */
        void setString(const std::string &string);

        /*!
         * @brief Return the text.
         */
        sf::Text &getText();

        /*!
         * @brief Set the text.
         * @param text Text which should be used
         */
        void setText(const sf::Text &text);

        /*!
         * @brief return a boolean indicating if the text is set.
         */
        bool isTextSet() const;

        /*!
         * @brief invalid the Text of the component.
         */
        void invalidateText();

        /*!
         * @brief return the id of the font used to display the text.
         */
        int getFontId() const;

        /*!
         * @brief Set the color of the text.
         */
        void setColorText(const sf::Color &color);

        /*!
         * @brief Set the outline color of the text.
         */
        void setOutlineColorText(const sf::Color &color);

    private:
        std::weak_ptr<ecs::IEntity> _entity;
        std::unique_ptr<sf::Text> _text; /*!< The text displayed */
        bool _textIsSet; /*!< Bool indicating if the font has been set */
        std::string _string; /*!< String with the content of the text */
        int _fontId; /*!< Id of the font to use */
    };
}

#endif // _TEXT_COMPONENT_HPP_
