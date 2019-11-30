/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageSystemApi.hpp
*/

/* Created the 28/11/2019 at 04:28 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DAMAGESYSTEMAPI_HPP
#define R_TYPE_DAMAGESYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace systems {

    /*!
     * @class DamageSystemApi
     * @brief Damage api
     */
    class DamageSystemApi : public ecs::ISystemAPI {
    public:
        static const ecs::Version Version;

    public:
        const ecs::Version &getVersion() const override;
        std::shared_ptr<ecs::ISystem> createNewSystem() const override;
    };
}

#endif //R_TYPE_DAMAGESYSTEMAPI_HPP
