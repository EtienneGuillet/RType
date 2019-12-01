/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DisplayableComponent.hpp
*/

/* Created the 28/11/2019 at 03:13 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DISPLAYABLECOMPONENT_HPP
#define R_TYPE_DISPLAYABLECOMPONENT_HPP

#include "ecs/IComponent/AComponent.hpp"
#include "rtype/game/RTypeEntityType.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class DisplayableComponent
         * @brief A displayable entity
         */
        class DisplayableComponent : public ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            DisplayableComponent(uint32_t type = rtype::ET_UNKNOWN);
            ~DisplayableComponent() = default;
            DisplayableComponent(const DisplayableComponent &other) = default;
            DisplayableComponent &operator=(const DisplayableComponent &rhs) = default;

        public:
            /*!
             * @brief Get the type of entity to display
             * @return the type of entity
             */
            uint32_t getType() const;
            /*!
             * @brief Set the type of entity to display
             * @param type the new type
             */
            void setType(uint32_t type);

        private:
            uint32_t _type; /*!< The type to display */
        };
    }
}

#endif //R_TYPE_DISPLAYABLECOMPONENT_HPP