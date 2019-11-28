/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkIdentityComponent.hpp
*/

/* Created the 28/11/2019 at 02:14 by julian.frabel@epitech.eu */

#ifndef R_TYPE_NETWORKIDENTITYCOMPONENT_HPP
#define R_TYPE_NETWORKIDENTITYCOMPONENT_HPP

#include "ecs/IEntity/AComponent.hpp"

namespace ecs {

    namespace components {

        /*!
         * @class NetworkIdentityComponent
         * @brief A network identity component
         */
        class NetworkIdentityComponent : ecs::AComponent {
        public:
            static const ecs::Version Version;
            const ecs::Version &getVersion() const override;

        public:
            NetworkIdentityComponent(uint32_t id = 0);
            ~NetworkIdentityComponent() = default;
            NetworkIdentityComponent(const NetworkIdentityComponent &other) = default;
            NetworkIdentityComponent &operator=(const NetworkIdentityComponent &rhs) = default;

        public:
            /*!
             * @brief Set network id
             * @param id the id to set
             */
            void setNetworkId(uint32_t id);
            /*!
             * @brief Get network id
             * @return the id
             */
            uint32_t getNetworkId() const;

        private:
            uint32_t _id; /*!< Entity network id */
        };
    }
}
#endif //R_TYPE_NETWORKIDENTITYCOMPONENT_HPP
