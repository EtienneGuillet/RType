/*
** EPITECH PROJECT, 2022
** TextComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef _TEXT_COMPONENT_HPP_
#define _TEXT_COMPONENT_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"
#include <SFML/Graphics.hpp>

namespace rtype {

    class ShapeComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        ShapeComponent();
        ShapeComponent();
        ~ShapeComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

    private:
        std::weak_ptr<ecs::IEntity> _entity;

    };
} /*rtype */

#endif // _TEXT_COMPONENT_HPP_
