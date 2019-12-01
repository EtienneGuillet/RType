/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RigidbodyComponent.hpp
*/

/* Created the 28/11/2019 at 02:50 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RIGIDBODYCOMPONENT_HPP
#define R_TYPE_RIGIDBODYCOMPONENT_HPP

#include <maths/Vectors.hpp>
#include "ecs/IComponent/AComponent.hpp"
#include "maths/Vectors.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class RigidbodyComponent
         * @brief A component used to compute physics
         */
        class RigidbodyComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            RigidbodyComponent(float ups = 1, const b12software::maths::Vector2D &direction = b12software::maths::Vector2D(), bool lookTowardsDirection = false);
            ~RigidbodyComponent() = default;
            RigidbodyComponent(const RigidbodyComponent &other) = default;
            RigidbodyComponent &operator=(const RigidbodyComponent &other) = default;

        public:
            /*!
             * @brief Get the direction of this component
             * @return the direction of this component
             */
            const b12software::maths::Vector2D &getDirection() const;
            /*!
             * @brief Set the direction of this component
             * @param direction The direction of this component
             */
            void setDirection(const b12software::maths::Vector2D &direction);
            /*!
             * @brief Get movement speed in unit per second
             * @return the movement speed
             */
            float getUps() const;
            /*!
             * @brief Set the movement speed in unit per second
             * @param ups the movement speed in unit per second
             */
            void setUps(float ups);
            /*!
             * @brief Get if the entity should look toward the direction
             * @return true or false
             */
            bool shouldLookTowardsDirection() const;
            /*!
             * @brief Set if the entity should look toward the direction
             * @param lookTowardsDirection new value
             */
            void setLookTowardsDirection(bool lookTowardsDirection);

        private:
            b12software::maths::Vector2D _direction; /*!< The direction of this rb */
            float _ups; /*!< movement unit per second */
            bool _lookTowardsDirection; /*!< Should the entity look towards the direction pointer */
        };
    }
}

#endif //R_TYPE_RIGIDBODYCOMPONENT_HPP
