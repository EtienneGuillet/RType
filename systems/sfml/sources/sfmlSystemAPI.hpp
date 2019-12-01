/*
** EPITECH PROJECT, 2022
** sfmlSystemAPI.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_SFMLSYSTEMAPI_HPP
#define R_TYPE_SFMLSYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

class SfmlSystemAPI : public ecs::ISystemAPI {

    public:

    [[nodiscard]] const ecs::Version &getVersion() const override;

    [[nodiscard]] std::shared_ptr<ecs::ISystem> createNewSystem() const override;

    static const ecs::Version Version;
};

#endif //R_TYPE_SFMLSYSTEMAPI_HPP
