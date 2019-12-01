/*
** EPITECH PROJECT, 2022
** TTLComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _MUSIC_COMPONENT_HPP_
#define _MUSIC_COMPONENT_HPP_

#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ecs/IComponent/AComponent.hpp>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class TTLComponent
     * @brief This class is a component allowing to choose the position the scale and the rotation of an entity.
     */
    class MusicComponent : public ecs::AComponent {

    public:
        static const ecs::Version Version;

        /*!
         * @brief Ctor.
         * @param pos Vectore3 indicating the position of the entity
         * @param rot Vectore2 indicating the rotation of the entity
         * @param scale Vectore2 indicating the scale of the entity
         */
        MusicComponent();

        /*!
         * @brief Dtor.
         */
        ~MusicComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;
        void setMusic(const std::string &music);
        void play();
        bool isSeted() const;

    private:
        std::weak_ptr<ecs::IEntity> _entity;
        sf::Music _music;
        bool _isSet;
    };
} /* rtype */

#endif // _TTL_COMPONENT_HPP_
