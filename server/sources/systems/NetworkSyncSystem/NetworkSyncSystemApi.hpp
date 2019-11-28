/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkSyncSystemApi.hpp
*/

/* Created the 28/11/2019 at 07:36 by julian.frabel@epitech.eu */

#ifndef R_TYPE_NETWORKSYNCSYSTEMAPI_HPP
#define R_TYPE_NETWORKSYNCSYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace systems {

    /*!
     * @class NetworkSyncSystemApi
     * @brief A system that sync network information with ecs components
     */
    class NetworkSyncSystemApi : public ecs::ISystemAPI {
    public:
        static const ecs::Version Version;

    public:
        const ecs::Version &getVersion() const override;
        std::shared_ptr<ecs::ISystem> createNewSystem() const override;
    };
}

#endif //R_TYPE_NETWORKSYNCSYSTEMAPI_HPP
