/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** NetworkSyncSystem.hpp
*/

/* Created the 28/11/2019 at 07:39 by julian.frabel@epitech.eu */

#ifndef R_TYPE_NETWORKSYNCSYSTEM_HPP
#define R_TYPE_NETWORKSYNCSYSTEM_HPP

#include <ecs/ASystem/ASystem.hpp>
#include <rtype/network/GameInfos.hpp>

namespace systems {

    /*!
     * @class NetworkSyncSystem
     * @brief A system that sync the network with ecs components
     */
    class NetworkSyncSystem : public ecs::ASystem {
    public:
        static const ecs::Version Version;

    public:
        NetworkSyncSystem();
        ~NetworkSyncSystem() = default;
        NetworkSyncSystem(const NetworkSyncSystem &other);
        NetworkSyncSystem &operator=(const NetworkSyncSystem &rhs);
        void tick(long deltatime) override;
        const ecs::Version &getType() const override;

    public:
        /*!
         * @brief Set the game infos datas
         * @param ptr the ptr to set
         */
        void setGameInfosPtr(std::weak_ptr<rtype::GameInfos> ptr);
        /*!
         * @brief Was game infos already set
         * @return true if game infos was already set false otherwise
         */
        bool areGameInfosSet() const;

    private:
        std::weak_ptr<rtype::GameInfos> _ptr; /*!< the pointer to the game infos */
        bool _valid; /*!< Is the pointer set and valid */
        long _elapsedTime; /*!< Elapsed time since last sync */
        long _timeBetweenSync; /*!< Theoritical time between network sync */
    };
}

#endif //R_TYPE_NETWORKSYNCSYSTEM_HPP
