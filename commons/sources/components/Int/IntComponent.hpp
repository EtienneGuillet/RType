/*
** EPITECH PROJECT, 2022
** IntComponent.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_INTCOMPONENT_HPP
#define R_TYPE_INTCOMPONENT_HPP

#include <ecs/IComponent/AComponent.hpp>
#include "logger/DefaultLogger.hpp"


class IntComponent : public ecs::AComponent {

public:
    static const ecs::Version Version;

    explicit IntComponent(int value);
    ~IntComponent() override = default;

    [[nodiscard]] const ecs::Version &getVersion() const override;

    int operator++();
private:
    int _value;

};

#endif //R_TYPE_INTCOMPONENT_HPP
