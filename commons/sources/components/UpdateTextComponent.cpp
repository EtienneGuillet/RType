/*
** EPITECH PROJECT, 2022
** UpdateTextComponent.cpp
** File description:
** Created by tpautier,
*/

#include "UpdateTextComponent.hpp"

const ecs::Version rtype::UpdateTextComponent::Version = ecs::Version("UpdateTextComponent", 0, 0, 0, 1);

rtype::UpdateTextComponent::UpdateTextComponent(const bool isUpdatable)
:_isUpdatable(isUpdatable)
{
}

void rtype::UpdateTextComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
{
    _entity = entity;
}

const ecs::Version &rtype::UpdateTextComponent::getVersion() const
{
    return UpdateTextComponent::Version;
}

void rtype::UpdateTextComponent::setHoverable(const bool isUpdatable)
{
    _isUpdatable = isUpdatable;
}

bool rtype::UpdateTextComponent::getHoverable() const
{
    return _isUpdatable;
}
