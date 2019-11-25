/*
** EPITECH PROJECT, 2022
** ShapeComponent.cpp
** File description:
** Created by tpautier,
*/

#include "AShapeComponent.hpp"

namespace rtype {

    AShapeComponent::AShapeComponent(const int type)
        :_type(type)
    {
    }

    void AShapeComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &AShapeComponent::getVersion() const
    {
        return AShapeComponent::Version;
    }

    void AShapeComponent::setType(const int type)
    {
        _type = type;
    }

    int AShapeComponent::getType() const
    {
        return _type;
    }
} /* rtype */
