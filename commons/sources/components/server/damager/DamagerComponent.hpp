/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamagerComponent.hpp
*/

/* Created the 28/11/2019 at 03:05 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DAMAGERCOMPONENT_HPP
#define R_TYPE_DAMAGERCOMPONENT_HPP

#include "ecs/IComponent/AComponent.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class DamagerComponent
         * @brief A component given to object that can inflic damages
         */
        class DamagerComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            DamagerComponent(uint32_t damages = 1, bool destroyOnHit = true, int layer = 0xffff);
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
            /*!
             * @brief Get the damage layer mask
             * @return the damage layer mask
             */
            int getDamageLayer() const;
            /*!
             * @brief Set the damage layer mask
             * @param damageLayer the damage layer mask
             */
            void setDamageLayer(int damageLayer);
            /*!
             * @brief get the owner of this damageable
             * @return the entity id of the owner
             */
            int getOwner() const;
            /*!
             * @brief Set the owner of the damager
             * @param owner the owner of the damager
             */
            void setOwner(int owner);

        private:
            uint32_t _damages; /*!< The damages inflicted by this entity */
            bool _destroyOnHit; /*!< Should the entity be deleted on hit */
            int _damageLayer; /*!< The damage layer 0b1 allies 0b10 enemies */
            int _owner; /*!< Id of the owner of this damageable */
        };
    }
}

#endif //R_TYPE_DAMAGERCOMPONENT_HPP
