/*
** EPITECH PROJECT, 2022
** MusicComponent.cpp
** File description:
** Created by tpautier,
*/

#include "MusicComponent.hpp"

namespace rtype {

    const ecs::Version MusicComponent::Version = ecs::Version("MusicComponent", 0, 0, 0, 1);

    MusicComponent::MusicComponent()
    :_isSet(false)
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test MusicComponent");
    }

    void MusicComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &MusicComponent::getVersion() const
    {
        return MusicComponent::Version;
    }

    void MusicComponent::setMusic(const std::string &music)
    {
        _isSet = true;
        _music.openFromFile(music);
        _music.setLoop(true);
    }

    void MusicComponent::play()
    {
        _music.play();
    }

    bool MusicComponent::isSeted() const
    {
        return _isSet;
    }
} /* rtype */
