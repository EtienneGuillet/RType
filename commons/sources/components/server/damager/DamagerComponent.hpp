/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamagerComponent.hpp
*/

/* Created the 28/11/2019 at 03:05 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DAMAGERCOMPONENT_HPP
#define R_TYPE_DAMAGERCOMPONENT_HPP

#include "ecs/IEntity/AComponent.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class DamagerComponent
         * @brief A component given to object that can inflic damages
         */
        class DamagerComponent : public ecs::AComponent {
        public:
            DamagerComponent(uint32_t damages = 1, bool destroyOnHit = true);
            ~DamagerComponent() = default;
            DamagerComponent(const DamagerComponent &other) = default;
            DamagerComponent &operator=(const DamagerComponent &rhs) = default;

        public:
            /*!
             * @brief Get the damages deal by this entity
             * @return the damages dealled
             */
            uint32_t getDamages() const;
            /*!
             * @brief set the damages of the entity
             * @param damages the damages of the entity
             */
            void setDamages(uint32_t damages);
            /*!
             * @brief Should this entity be destroyed on hit
             * @return true if this should be destroyed on hit false otherwise
             */
            bool isDestroyOnHit() const;
            /*!
             * @brief Set destroy on hit
             * @param destroyOnHit destroy on hit
             */
            void setDestroyOnHit(bool destroyOnHit);

        private:
            uint32_t _damages; /*!< The damages inflicted by this entity */
            bool _destroyOnHit; /*!< Should the entity be deleted on hit */
        };
    }
}

#endif //R_TYPE_DAMAGERCOMPONENT_HPP
