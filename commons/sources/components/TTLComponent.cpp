/*
** EPITECH PROJECT, 2022
** TTLComponent.cpp
** File description:
** Created by tpautier,
*/

#include "TTLComponent.hpp"

namespace rtype {

    const ecs::Version TTLComponent::Version = ecs::Version("TTLComponent", 0, 0, 0, 1);

    TTLComponent::TTLComponent()
    :_ttl(std::chrono::system_clock::now())
    {
        // b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test TTLComponent");
    }

    void TTLComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &TTLComponent::getVersion() const
    {
        return TTLComponent::Version;
    }

    void TTLComponent::updateTTL()
    {
        _ttl = std::chrono::system_clock::now();
    }

    const std::chrono::time_point<std::chrono::system_clock> &TTLComponent::getTTL()
    {
        return _ttl;
    }
} /* rtype */
