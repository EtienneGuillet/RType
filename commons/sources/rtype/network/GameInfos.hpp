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
#include "PlayerInfos.hpp"
#include "EntityInfos.hpp"
#include "containers/ThreadSafeList.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    class GameInfos : public std::enable_shared_from_this<GameInfos> {
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

        /*!
         * @brief Get a weak ptr to this object
         * @return A weak ptr to this object
         */
        std::weak_ptr<GameInfos> getWeak();

    private:
        std::atomic_int _nbPlayers; /*!< Number of players */
        PlayerInfos _players[4]; /*!< The players */
        b12software::containers::ThreadSafeList<rtype::EntityInfos> _entities; /*!< A list of entities to sync on the network */
    };
}

#endif //R_TYPE_GAMEINFOS_HPP
