/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** GameInfos.hpp
*/

/* Created the 27/11/2019 at 13:46 by julian.frabel@epitech.eu */

#ifndef R_TYPE_GAMEINFOS_HPP
#define R_TYPE_GAMEINFOS_HPP

#include <functional>
    "bits/c++config.h"
    "bits/stl_function.h"
        "bits/stl_algo.h"
            "bits/c++config.h"
            "bits/stl_algo.h"
                "bits/c++config.h"
                "bits/exception.h"
                    "bits/exception_ptr.h"
                    "bits/nested_exception.h"
        "bits/stl_algo.h"
                "bits/stl_algo.h"
                    "bits/c++config.h"
                    "bits/stl_relops.h"
                    "bits/stl_pair.h"
                        "bits/stl_algo.h"
                        "bits/move.h"
                        "bits/stl_algo.h"
                                "bits/c++config.h"
                "bits/stl_algo.h"
                        "bits/stl_algo.h"
                        "bits/stl_algo.h"
                            "bits/stl_algo.h"
                            "bits/stl_algo.h"
                                "bits/c++config.h"
                                "bits/stringfwd.h"
                                "bits/char_traits.h"
                                "bits/allocator.h"
                                "bits/cpp_type_traits.h"
                                "bits/localefwd.h"
                                "bits/ostream_insert.h"
                                "bits/stl_iterator_base_types.h"
                                "bits/stl_iterator_base_funcs.h"
                                "bits/stl_iterator.h"
                                "bits/stl_function.h"
                                "ext/numeric_traits.h"
                                "bits/stl_algobase.h"
                                "bits/range_access.h"
                                "bits/basic_string.h"
                                "bits/basic_string.tcc"
                        "bits/stl_algobase.h"
                        "bits/range_access.h"
                "bits/uses_allocator.h"
                "bits/invoke.h"
        "bits/stl_algo.h"
        "bits/functional_hash.h"
        "bits/invoke.h"
        "bits/refwrap.h"
        "bits/std_function.h"
            "bits/stl_algo.h"
                    "bits/stl_algo.h"
                    "bits/stl_algo.h"
                    "bits/allocator.h"
                    "ext/alloc_traits.h"
                    "ext/aligned_buffer.h"
                    "bits/stl_pair.h"
                    "bits/stl_function.h"
                    "bits/functional_hash.h"
                    "bits/hashtable.h"
                    "bits/unordered_map.h"
                    "bits/range_access.h"
                    "bits/erase_if.h"
            "bits/stl_algo.h"
                "bits/stl_algobase.h"
                "bits/allocator.h"
                "bits/stl_construct.h"
                "bits/stl_uninitialized.h"
                "bits/stl_vector.h"
                "bits/stl_bvector.h"
                "bits/range_access.h"
                    "bits/vector.tcc"
            "bits/stl_algo.h"
            "bits/stl_algo.h"
            "bits/stl_algo.h"
#include "PlayerInfos.hpp"
#include "EntityInfos.hpp"
#include "containers/ThreadSafeList.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    class GameInfos {
    public:
        GameInfos();
        ~GameInfos();
        GameInfos(const GameInfos &other);
        GameInfos &operator=(const GameInfos &rhs);

    public:
        /*!
         * @brief reset this game informations
         */
        void reset();

    public:
        /*!
         * @brief get the number of players
         * @return the number of players
         */
        int getNbPlayers() const;
        /*!
         * @brief Set the number of players
         * @param nbPlayer The new number of players
         */
        void setNbPlayers(int nbPlayer);

        /*!
         * @brief Get a player by it's index
         * @param nb the index of the player
         * @return the player
         */
        PlayerInfos &getPlayer(int nb);
        /*!
         * @brief Get a player by it's index
         * @param nb the index of the player
         * @return the player
         */
        const PlayerInfos &getPlayer(int nb) const;
        /*!
         * @brief Set a player by it's index
         * @param nb the index of the player
         * @param infos the player
         */
        void setPlayer(int nb, const PlayerInfos &infos);

        /*!
         * @brief Get the entities
         * @return the entities
         */
        b12software::containers::ThreadSafeList<rtype::EntityInfos> &getEntities();
        /*!
         * @brief Get the entities
         * @return the entities
         */
        const b12software::containers::ThreadSafeList<rtype::EntityInfos> &getEntities() const;
        /*!
         * @brief Set the entities
         * @param entities the entities to set
         */
        void setEntities(const b12software::containers::ThreadSafeList<rtype::EntityInfos> &entities);

        /*!
         * @brief Add an entity to sync on the network
         * @param entity the entity to sync
         */
        void addEntity(const rtype::EntityInfos &entity);
        /*!
         * @brief Remove an entity from the list by id
         * @param id the id to remove
         */
        void removeEntity(uint32_t id);
        /*!
         * @brief Remove an entity from the list by id
         * @param entity the entity to remove
         */
        void removeEntity(const rtype::EntityInfos &entity);
        /*!
         * @brief Remove entities that match the function given (where the function returns true)
         * @param func the function to use
         */
        void removeEntities(const std::function<bool(const rtype::EntityInfos &)> &func);

    private:
        std::atomic_int _nbPlayers; /*!< Number of players */
        PlayerInfos _players[4]; /*!< The players */
        b12software::containers::ThreadSafeList<rtype::EntityInfos> _entities; /*!< A list of entities to sync on the network */
    };
}

#endif //R_TYPE_GAMEINFOS_HPP
