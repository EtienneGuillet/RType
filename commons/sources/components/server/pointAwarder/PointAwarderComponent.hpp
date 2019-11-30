/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PointAwarderComponent.hpp
*/

/* Created the 28/11/2019 at 06:56 by julian.frabel@epitech.eu */

#ifndef R_TYPE_POINTAWARDERCOMPONENT_HPP
#define R_TYPE_POINTAWARDERCOMPONENT_HPP

#include "ecs/IComponent/AComponent.hpp"

namespace ecs {

    namespace components {
        /*!
         * @class PointAwarderComponent
         * @brief A point awarder component
         */
        class PointAwarderComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            PointAwarderComponent(int points = 500);
            ~PointAwarderComponent() = default;
            PointAwarderComponent(const PointAwarderComponent &other) = default;
            PointAwarderComponent &operator=(const PointAwarderComponent &rhs) = default;

        public:
            /*!
             * @brief get the amount of awarded points
             * @return points
             */
            int getPoints() const;
            /*!
             * @brief set the amount of awarded points
             * @param points the amount of awarded points
             */
            void setPoints(int points);

        private:
            int _points; /*!< Amount of awarded points */
        };
    }
}

#endif //R_TYPE_POINTAWARDERCOMPONENT_HPP
