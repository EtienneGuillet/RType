/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** WeaponComponent.hpp
*/

/* Created the 28/11/2019 at 02:25 by julian.frabel@epitech.eu */

#ifndef R_TYPE_WEAPONCOMPONENT_HPP
#define R_TYPE_WEAPONCOMPONENT_HPP

#include "ecs/IComponent/AComponent.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class WeaponComponent
         * @brief A component for a weapon
         */
        class WeaponComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            /*!
             * @enum WeaponType
             * @brief An enum for a default weapon type
             */
            enum WeaponType {
                WEAPON_TYPE_STANDARD_WAVE_CANON, /*!< A standard wave canon */
            };

        public:
            WeaponComponent(WeaponType type = WEAPON_TYPE_STANDARD_WAVE_CANON, uint32_t chargeTime = 1000);
            ~WeaponComponent() = default;
            WeaponComponent(const WeaponComponent &other) = default;
            WeaponComponent &operator=(const WeaponComponent &rhs) = default;

        public:
            /*!
             * @brief Get the type of weapon
             * @return The type of weapon
             */
            WeaponType getType() const;
            /*!
             * @briefSet the type of weapon
             * @param type the new type of weapon
             */
            void setType(WeaponType type);
            /*!
             * @brief Get the weapon charge time in milliseconds seconds for this weapon
             * @return rpms
             */
            uint32_t getChargeTime() const;
            /*!
             * @brief Set the weapon charge time in milliseconds seconds for this weapon
             * @param ms new charge time per milliseconds seconds
             */
            void setChargeTime(uint32_t ms);

        private:
            WeaponType _type; /*!< The type of weapon for this entity */
            uint32_t _chargeTime; /*!< Rounds charge time in millisecond second */
        };
    }
}

#endif //R_TYPE_WEAPONCOMPONENT_HPP
