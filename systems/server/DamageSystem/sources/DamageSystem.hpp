/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageSystem.hpp
*/

/* Created the 28/11/2019 at 04:28 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DAMAGESYSTEM_HPP
#define R_TYPE_DAMAGESYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>
#include <maths/Vectors.hpp>

namespace systems {

    /*!
     * @class DamageSystem
     * @brief Damage system
     */
    class DamageSystem : public ecs::ASystem {
    public:
        DamageSystem();
    public:
        static const ecs::Version Version;

    public:
        void tick(long deltatime) override;
        [[nodiscard]] const ecs::Version &getType() const override;
        void start() override;
        void stop() override;

    private:
        /*!
         * @brief Do the actual damage computation
         */
        void computeDamages() const;
        /*!
         * @brief Compute if col A collides with col B
         * @param colAPos The position of collider A
         * @param colASize The size of collider A
         * @param colBPos The position of collider B
         * @param colBSize The size of collider B
         * @return true if a collision occur false otherwise
         */
        static bool collide(const b12software::maths::Vector2D &colAPos, const b12software::maths::Vector2D &colASize,
            const b12software::maths::Vector2D &colBPos, const b12software::maths::Vector2D &colBSize);

    private:
        long _elapsedTime; /*!< The passed elapsed time in ms */
        long _computeEvery; /*!< Compute actual damages every x ms*/
    };
}

#endif //R_TYPE_DAMAGESYSTEM_HPP
