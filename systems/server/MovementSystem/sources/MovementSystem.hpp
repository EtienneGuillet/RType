/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** MovementSystem.hpp
*/

/* Created the 28/11/2019 at 03:28 by julian.frabel@epitech.eu */

#ifndef R_TYPE_MOVEMENTSYSTEM_HPP
#define R_TYPE_MOVEMENTSYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>

namespace systems {

    /*!
     * @class MovementSystem
     * @brief Movement system
     */
    class MovementSystem : public ecs::ASystem {
    public:
        static const ecs::Version Version;

    public:
        void tick(long deltatime) override;
        const ecs::Version &getType() const override;
    };
}

#endif //R_TYPE_MOVEMENTSYSTEM_HPP
