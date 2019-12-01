/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkMovementLagCompensation.hpp
*/

/* Created the 01/12/2019 at 19:52 by julian.frabel@epitech.eu */

#ifndef R_TYPE_NETWORKMOVEMENTLAGCOMPENSATION_HPP
#define R_TYPE_NETWORKMOVEMENTLAGCOMPENSATION_HPP

#include "ecs/ASystem/ASystem.hpp"

namespace rtype {

    class NetworkMovementLagCompensation : public ecs::ASystem {
    public:
        virtual const ecs::Version &getType() const override;
        virtual void tick(long deltatime) override;

    public:
        static const ecs::Version Version;
    };
}

#endif //R_TYPE_NETWORKMOVEMENTLAGCOMPENSATION_HPP
