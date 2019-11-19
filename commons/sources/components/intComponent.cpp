/*
** EPITECH PROJECT, 2022
** intComponent.cpp
** File description:
** Created by tpautier,
*/

#include "intComponent.hpp"

const ecs::Version intComponent::Version = ecs::Version("intComponent", 0, 1, 0, 0);

intComponent::intComponent(int value)
    : _value(value)
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test intComponent");
}

void intComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
{
    _entity = entity;
}

const ecs::Version& intComponent::getVersion() const
{
    return intComponent::Version;
}