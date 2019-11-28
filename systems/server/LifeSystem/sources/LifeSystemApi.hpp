/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** LifeSystemApi.hpp
*/

/* Created the 28/11/2019 at 06:08 by julian.frabel@epitech.eu */

#ifndef R_TYPE_LIFESYSTEMAPI_HPP
#define R_TYPE_LIFESYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace systems {

    /*!
     * @class LifeSystemApi
     * @brief life system api
     */
    class LifeSystemApi : public ecs::ISystemAPI {
    public:
        static const ecs::Version Version;

    public:
        const ecs::Version &getVersion() const override;
        std::shared_ptr<ecs::ISystem> createNewSystem() const override;
    };
}

#endif //R_TYPE_LIFESYSTEMAPI_HPP
