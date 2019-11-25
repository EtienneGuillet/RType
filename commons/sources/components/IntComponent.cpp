/*
** EPITECH PROJECT, 2022
** IntComponent.cpp
** File description:
** Created by tpautier,
*/

#include "IntComponent.hpp"

const ecs::Version rtype::IntComponent::Version = ecs::Version("IntComponent", 0, 1, 0, 0);

rtype::IntComponent::IntComponent(int value)
    : _value(value)
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test IntComponent");
}

void rtype::IntComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
{
    _entity = entity;
}

const ecs::Version& rtype::IntComponent::getVersion() const
{
    return IntComponent::Version;
}

int rtype::IntComponent::operator++() {
    _value++;

    return _value;
}
