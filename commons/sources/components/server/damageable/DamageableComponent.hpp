/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DamageableComponent.hpp
*/

/* Created the 28/11/2019 at 01:45 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DAMAGEABLECOMPONENT_HPP
#define R_TYPE_DAMAGEABLECOMPONENT_HPP

#include "ecs/IEntity/AComponent.hpp"

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
            explicit DamageableComponent(int hp = 3, int maxHp = 3, long invulnerabilityPeriod = 0);
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

        private:
            int _hp; /*!< The hp of this damageable component */
            int _maxHp; /*!< The maximal amount of hp */
            long _invulnerabilityPeriodAfterDamage; /*!< Amount of time after damage in ms for invulnerability */
            long _invulnerabilityRemaining; /*!< Amount of time remaining in ms for invulnerability */
        };
    }
}

#endif //R_TYPE_DAMAGEABLECOMPONENT_HPP
