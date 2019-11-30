/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** MovementSystemApi.hpp
*/

/* Created the 28/11/2019 at 03:28 by julian.frabel@epitech.eu */

#ifndef R_TYPE_MOVEMENTSYSTEMAPI_HPP
#define R_TYPE_MOVEMENTSYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

namespace systems {

    /*!
     * @class MovementSystemApi
     * @brief Movement api
     */
    class MovementSystemApi : public ecs::ISystemAPI {
    public:
        static const ecs::Version Version;

    public:
        const ecs::Version &getVersion() const override;
        std::shared_ptr<ecs::ISystem> createNewSystem() const override;
    };
}

#endif //R_TYPE_MOVEMENTSYSTEMAPI_HPP
