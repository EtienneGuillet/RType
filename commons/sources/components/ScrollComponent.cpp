/*
** EPITECH PROJECT, 2022
** ScrollComponent.cpp
** File description:
** Created by tpautier,
*/

#include "ScrollComponent.hpp"

namespace rtype {

    const ecs::Version ScrollComponent::Version = ecs::Version("ScrollComponent", 0, 0, 0, 1);

    ScrollComponent::ScrollComponent()
    : _scrollValues()
    {
    }

    void ScrollComponent::setEntity(const std::weak_ptr<ecs::IEntity> &entity)
    {
        _entity = entity;
    }

    const ecs::Version &ScrollComponent::getVersion() const
    {
        return ScrollComponent::Version;
    }

    void ScrollComponent::setScrollValues(const sf::Vector2<float> &scrollValues)
    {
        _scrollValues = scrollValues;
    }

    const sf::Vector2<float> &ScrollComponent::getScrollValues() const
    {
        return _scrollValues;
    }
}
