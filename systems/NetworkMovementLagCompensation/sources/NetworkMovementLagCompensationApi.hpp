/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkMovementLagCompensationApi.hpp
*/

/* Created the 01/12/2019 at 19:50 by julian.frabel@epitech.eu */

#ifndef R_TYPE_NETWORKMOVEMENTLAGCOMPENSATIONAPI_HPP
#define R_TYPE_NETWORKMOVEMENTLAGCOMPENSATIONAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace rtype {

    class NetworkMovementLagCompensationApi : public ecs::ISystemAPI {
    public:
        [[nodiscard]] const ecs::Version &getVersion() const override;

        [[nodiscard]] std::shared_ptr<ecs::ISystem> createNewSystem() const override;

    public:
        static const ecs::Version Version;
    };
}

#endif //R_TYPE_NETWORKMOVEMENTLAGCOMPENSATIONAPI_HPP
