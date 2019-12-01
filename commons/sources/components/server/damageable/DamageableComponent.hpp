/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageableComponent.hpp
*/

/* Created the 28/11/2019 at 01:45 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DAMAGEABLECOMPONENT_HPP
#define R_TYPE_DAMAGEABLECOMPONENT_HPP

#include "ecs/IComponent/AComponent.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class DamageableComponent
         * @brief A damageable component
         */
        class DamageableComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            explicit DamageableComponent(int hp = 3, int maxHp = 3, long invulnerabilityPeriod = 0, int damageLayer = 0xffff);
            ~DamageableComponent() = default;
            DamageableComponent(const DamageableComponent &other) = default;
            DamageableComponent &operator=(const DamageableComponent &rhs) = default;

        public:
            /*!
             * @brief Set the hp variable ensuring it does not pass maxHp
             * @param hp the hp value to set
             */
            void setHp(int hp);
            /*!
             * @brief Set the maximal number of hp for this hp reducing hp if bigger than new max hp
             * @param maxHp the maxhp
             */
            void setMaxHp(int maxHp);

        public:
            /*!
             * @brief Heal this entity by amount ensuring that hp does not goes over max HP
             * @param amount the amount to heal
             */
            void heal(int amount);
            /*!
             * @brief Damage this entity by amount ensuring that hp does not go under 0
             * @param amount the amount of damage
             */
            void damage(int amount);
            /*!
             * @brief Get the remaining hp
             * @return hp
             */
            int getHp() const;
            /*!
             * @brief Check if hp > 0
             * @return true if hp > 0 false otherwise
             */
            bool isAlive() const;

            /*!
             * @brief Get this entity maximal hp
             * @return maxHp
             */
            int getMaxHp() const;
            /*!
             * @brief Get invulnerability period
             * @return the invulnerability period in ms
             */
            long getInvulnerabilityPeriodAfterDamage() const;
            /*!
             * @brief Set the invulnerability period
             * @param invulnerabilityPeriodAfterDamage invulnerability period in ms
             */
            void setInvulnerabilityPeriodAfterDamage(long invulnerabilityPeriodAfterDamage);
            /*!
             * @brief Get invulnerability time remaining in ms
             * @return the invulnerability period remaining in ms
             */
            long getInvulnerabilityRemaining() const;
            /*!
             * @brief Set the invulnerability remaining in seconds
             * @param invulnerabilityRemaining invulnerability remaining in ms
             */
            void setInvulnerabilityRemaining(long invulnerabilityRemaining);
            /*!
             * @brief Check if is currently invulnerable
             * @return true if invulnerable
             */
            bool isInvulnerable() const;
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
             * @brief get the entity id of the owner of the last hit
             * @return the entity of the owner
             */
            int getLastHitOwner() const;
            /*!
             * @brief set the owner of the last hit
             * @param lastHitOwner the entity id of the owner
             */
            void setLastHitOwner(int lastHitOwner);

        private:
            int _hp; /*!< The hp of this damageable component */
            int _maxHp; /*!< The maximal amount of hp */
            long _invulnerabilityPeriodAfterDamage; /*!< Amount of time after damage in ms for invulnerability */
            long _invulnerabilityRemaining; /*!< Amount of time remaining in ms for invulnerability */
            int _damageLayer; /*!< The damage layer 0b1 allies 0b10 enemies */
            int _lastHitOwner; /*!< Owner of the person that last hitted this entity */
        };
    }
}

#endif //R_TYPE_DAMAGEABLECOMPONENT_HPP
