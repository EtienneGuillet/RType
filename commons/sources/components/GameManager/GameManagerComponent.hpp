/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** GameManagerComponent.hpp
*/

/* Created the 30/11/2019 at 06:03 by julian.frabel@epitech.eu */

#ifndef R_TYPE_GAMEMANAGERCOMPONENT_HPP
#define R_TYPE_GAMEMANAGERCOMPONENT_HPP

#include "ecs/IComponent/AComponent.hpp"
#include "rtype/client/NetworkState.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    class GameManagerComponent : public ecs::AComponent {
    public:
        GameManagerComponent(NetworkState &state, bool &shouldClose);
        ~GameManagerComponent() = default;
        GameManagerComponent(const GameManagerComponent &other) = default;
        GameManagerComponent &operator=(const GameManagerComponent &rhs) = default;

    public:
        /*!
         * @brief Get the state
         * @return the state
         */
        NetworkState &getState();

        /*!
         * @brief Get the should close reference
         * @return the reference
         */
        bool &getShouldClose();

    private:
        NetworkState &_state; /*!< The network state to sync */
        bool &_shouldClose; /*!< Should the program close */
    };
}

#endif //R_TYPE_GAMEMANAGERCOMPONENT_HPP
