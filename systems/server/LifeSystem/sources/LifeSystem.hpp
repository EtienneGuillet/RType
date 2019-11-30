/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** LifeSystem.hpp
*/

/* Created the 28/11/2019 at 06:09 by julian.frabel@epitech.eu */

#ifndef R_TYPE_LIFESYSTEM_HPP
#define R_TYPE_LIFESYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>

namespace systems {

    /*!
     * @class LifeSystem
     * @brief system that handle the entity dying mecanic
     */
    class LifeSystem : public ecs::ASystem {
    public:
        static const ecs::Version Version;

    public:
        void tick(long deltatime) override;
        const ecs::Version &getType() const override;
    };
}

#endif //R_TYPE_LIFESYSTEM_HPP
