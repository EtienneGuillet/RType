/*
** EPITECH PROJECT, 2022
** HoverComponent.cpp
** File description:
** Created by tpautier,
*/

#include "HoverComponent.hpp"

const ecs::Version rtype::HoverComponent::Version = ecs::Version("HoverComponent", 0, 0, 0, 1);

rtype::HoverComponent::HoverComponent(const bool isHoverable)
:_isHoverable(isHoverable)
{
}

void rtype::HoverComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
{
    _entity = entity;
}

const ecs::Version &rtype::HoverComponent::getVersion() const
{
    return HoverComponent::Version;
}

void rtype::HoverComponent::setHoverable(const bool isHoverable)
{
    _isHoverable = isHoverable;
}

bool rtype::HoverComponent::getHoverable() const
{
    return _isHoverable;
}
