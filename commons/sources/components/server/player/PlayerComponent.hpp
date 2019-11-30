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
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

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
            float getCharge() const;
            /*!
             * @brief Set the charge of this player weapon
             * @param charge the new charge of the weapon
             */
            void setCharge(float charge);
            /*!
             * @brief Is the shot button pressed
             * @return true or false
             */
            bool isShotPressed() const;
            /*!
             * @brief Set the shot button pressed
             * @param shotPressed is it pressed
             */
            void setShotPressed(bool shotPressed);
            /*!
             * @brief Was the shot button released
             * @return true if was released false otherwise
             */
            bool isReleased() const;
            /*!
             * @brief Set was released
             * @param released true if was released false otherwise
             */
            void setReleased(bool released);

        private:
            uint32_t _score; /*!< The score of this player */
            float _charge; /*!< The charge of this player */
            bool _shotPressed; /*!< Is the shot button pressed */
            bool _released; /*!< Was the shot button just released */
        };
    }
}

#endif //R_TYPE_PLAYERCOMPONENT_HPP
