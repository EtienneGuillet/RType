/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ColliderComponent.hpp
*/

/* Created the 28/11/2019 at 02:42 by julian.frabel@epitech.eu */

#ifndef R_TYPE_COLLIDERCOMPONENT_HPP
#define R_TYPE_COLLIDERCOMPONENT_HPP

#include "ecs/IEntity/AComponent.hpp"
#include "maths/Vectors.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class ColliderComponent
         * @brief A 2D collider
         */
        class ColliderComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            ColliderComponent(const b12software::maths::Vector2D &size = b12software::maths::Vector2D(1, 1), const b12software::maths::Vector2D &offset = b12software::maths::Vector2D());
            ~ColliderComponent() = default;
            ColliderComponent(const ColliderComponent &other) = default;
            ColliderComponent &operator=(const ColliderComponent &rhs) = default;

        public:
            /*!
             * @brief Get the size of this collider
             * @return collider size
             */
            const b12software::maths::Vector2D &getSize() const;
            /*!
             * @brief Set the size of this collider
             * @param size the new size
             */
            void setSize(const b12software::maths::Vector2D &size);
            /*!
             * @brief Get the offset from the transform/origin
             * @return the offset
             */
            const b12software::maths::Vector2D &getOffset() const;
            /*!
             * @brief Set the offset
             * @param offset the new offset
             */
            void setOffset(const b12software::maths::Vector2D &offset);

        private:
            b12software::maths::Vector2D _size; /*!< The size of this collider */
            b12software::maths::Vector2D _offset; /*!< Offset from transform / world origin */
        };
    }
}

#endif //R_TYPE_COLLIDERCOMPONENT_HPP
