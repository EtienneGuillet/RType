/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ClientGameNetworkEntitySyncSystemApi.hpp
*/

/* Created the 30/11/2019 at 12:49 by julian.frabel@epitech.eu */

#ifndef R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEMAPI_HPP
#define R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace rtype {

    class ClientGameNetworkEntitySyncSystemApi : public ecs::ISystemAPI {
    public:
        [[nodiscard]] const ecs::Version &getVersion() const override;

        [[nodiscard]] std::shared_ptr<ecs::ISystem> createNewSystem() const override;

    public:
        static const ecs::Version Version;
    };
}

#endif //R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEMAPI_HPP
