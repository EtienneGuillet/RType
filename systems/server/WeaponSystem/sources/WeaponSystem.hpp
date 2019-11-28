/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponSystem.hpp
*/

/* Created the 28/11/2019 at 11:12 by julian.frabel@epitech.eu */

#ifndef R_TYPE_WEAPONSYSTEM_HPP
#define R_TYPE_WEAPONSYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>

namespace systems {

    class WeaponSystem : public ecs::ASystem {
    public:
        static const ecs::Version Version;

    public:
        void tick(long deltatime) override;
        const ecs::Version &getType() const override;
    };
}

#endif //R_TYPE_WEAPONSYSTEM_HPP
