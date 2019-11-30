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
            WeaponComponent(WeaponType type = WEAPON_TYPE_STANDARD_WAVE_CANON, uint32_t rps = 1);
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
             * @brief Get the rounds per seconds for this weapon
             * @return rps
             */
            uint32_t getRps() const;
            /*!
             * @brief Set the rounds per seconds for this weapon
             * @param rps new rounds per seconds
             */
            void setRps(uint32_t rps);

        private:
            WeaponType _type; /*!< The type of weapon for this entity */
            uint32_t _rps; /*!< Rounds per second */
        };
    }
}

#endif //R_TYPE_WEAPONCOMPONENT_HPP
