/*
** EPITECH PROJECT, 2022
** IntComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_INTCOMPONENT_HPP
#define R_TYPE_INTCOMPONENT_HPP

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"


class IntComponent : public ecs::IComponent {

    public:
        static const ecs::Version Version;

        IntComponent(int value);
        ~IntComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

        int operator++();

    private:

    std::weak_ptr<ecs::IEntity> _entity;
    int _value;

};

#endif //R_TYPE_INTCOMPONENT_HPP
