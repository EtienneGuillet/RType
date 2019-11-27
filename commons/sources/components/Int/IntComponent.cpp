/*
** EPITECH PROJECT, 2022
** IntComponent.cpp
** File description:
** Created by tpautier,
*/

#include "IntComponent.hpp"

const ecs::Version IntComponent::Version = ecs::Version("IntComponent", 0, 1, 0, 0);

IntComponent::IntComponent(int value)
    : _value(value)
{
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::to_string(_value));
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "test IntComponent");
}

const ecs::Version& IntComponent::getVersion() const
{
    return IntComponent::Version;
}

int IntComponent::operator++() {
    _value++;

    return _value;
}
