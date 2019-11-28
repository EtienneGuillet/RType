/*
** EPITECH PROJECT, 2022
** GameState.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_GAMESTATE_HPP
#define R_TYPE_GAMESTATE_HPP

#include "EntitiesState.hpp"
#include <vector>
#include <algorithm>

/*!
 * @enum Keys
 * @brief Enum representing the
 */
enum Keys {
    Z,
    Q,
    S,
    D,
    SPACE,
    ESCAPE,
    ENTER
};

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class GameState
     * @brief Used to store information of all the entities for graphical and network purpose.
     */
    class GameState {

        public:

        /*!
         * @brief Ctor.
         */
        GameState() = default;

        /*!
         * @brief Dtor.
         */
        ~GameState() = default;

        /*!
         * @brief Add an entity to the vector of entities.
         * @param the entity to add.
         */
        void addEntity(const rtype::EntitiesState &entity);

        /*!
         * @brief Remove an entity to the vector of entities.
         * @param the id of the entity to remove.
         */
        void removeEntity(std::uint32_t id);

        /*!
         * @brief Get a entity.
         * @param id the id of the entity asked.
         * @return the entity found.
         */
        [[nodiscard]] const rtype::EntitiesState &getEntity(std::uint32_t id) const;

        /*!
         * @brief Get all the entities stored.
         * @return The vector of all the entities stored.
         */
        [[nodiscard]] const std::vector<rtype::EntitiesState> &getEntities() const;

        /*!
         * @brief Get a vector of entities that as the ids specified.
         * @param ids The ids of the entities wanted.
         * @return A copied vector of the entities found with the ids specified.
         */
        std::vector<rtype::EntitiesState> getEntities(const std::vector<std::uint32_t > &ids);

        /*
         * @brief Sort the vector of entities by there Position in Z axe.
         */
        void sortByZindex();

        /*!
         * @brief Set the inputs of the client.
         * @param A map of key and a bool, true or false whether the input is held or not.
         */
        void setInputs(const std::map<Keys, bool> &keys);

        /*!
         * @brief Get the inputs of the client.
         * @return A map of key and a bool, true or false whether the input is held or not.
         */
        const std::map<Keys, bool> &getInputs();


        private:

        static bool comparePositionZ(rtype::EntitiesState entity1, rtype::EntitiesState entity2);

        std::map<Keys, bool> _inputs;
        std::vector<rtype::EntitiesState> _entities;
    };
}

#endif //R_TYPE_GAMESTATE_HPP
