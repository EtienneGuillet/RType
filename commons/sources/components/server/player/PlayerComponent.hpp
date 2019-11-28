/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PlayerComponent.hpp
*/

/* Created the 28/11/2019 at 02:59 by julian.frabel@epitech.eu */

#ifndef R_TYPE_PLAYERCOMPONENT_HPP
#define R_TYPE_PLAYERCOMPONENT_HPP

#include "ecs/IEntity/AComponent.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class PlayerComponent
         * @brief A component representing a player
         */
        class PlayerComponent : public ecs::AComponent {
        public:
            PlayerComponent(uint32_t score = 0, uint8_t charge = 0);
            ~PlayerComponent() = default;
            PlayerComponent(const PlayerComponent &other) = default;
            PlayerComponent &operator=(const PlayerComponent &rhs) = default;

        public:
            /*!
             * @brief Get the score of this player
             * @return the score
             */
            uint32_t getScore() const;
            /*!
             * @brief Set the score for this player
             * @param score the score to set
             */
            void setScore(uint32_t score);
            /*!
             * @brief Get the charge of this player
             * @return the charge of the player
             */
            uint8_t getCharge() const;
            /*!
             * @brief Set the charge of this player weapon
             * @param charge the new charge of the weapon
             */
            void setCharge(uint8_t charge);

        private:
            uint32_t _score; /*!< The score of this player */
            uint8_t _charge; /*!< The charge of this player */
        };
    }
}

#endif //R_TYPE_PLAYERCOMPONENT_HPP
