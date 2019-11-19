/*
** EPITECH PROJECT, 2022
** intComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_INTCOMPONENT_HPP
#define R_TYPE_INTCOMPONENT_HPP

#include "ecs/IComponent/IComponent.hpp"
#include "logger/DefaultLogger.hpp"


class intComponent : public ecs::IComponent {

    public:

        intComponent(int value);
        ~intComponent() override = default;

        void setEntity(const std::weak_ptr<ecs::IEntity> &entity) override;
        const ecs::Version &getVersion() const override;

    private:

    std::weak_ptr<ecs::IEntity> _entity;
    static const ecs::Version Version;
    int _value;

};

#endif //R_TYPE_INTCOMPONENT_HPP
