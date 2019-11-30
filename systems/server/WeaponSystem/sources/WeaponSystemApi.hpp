/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponSystemApi.hpp
*/

/* Created the 28/11/2019 at 11:10 by julian.frabel@epitech.eu */

#ifndef R_TYPE_WEAPONSYSTEMAPI_HPP
#define R_TYPE_WEAPONSYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace systems {

    /*!
     * @class WeaponSystemApi
     * @brief load Weapon system
     */
    class WeaponSystemApi : public ecs::ISystemAPI {
    public:
        static const ecs::Version Version;

    public:
        const ecs::Version &getVersion() const override;
        std::shared_ptr<ecs::ISystem> createNewSystem() const override;
    };
}

#endif //R_TYPE_WEAPONSYSTEMAPI_HPP
