/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ClientGameNetworkEntitySyncSystem.hpp
*/

/* Created the 30/11/2019 at 12:48 by julian.frabel@epitech.eu */

#ifndef R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEM_HPP
#define R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEM_HPP

#include <map>
#include "ecs/ASystem/ASystem.hpp"
#include "ecs/Version/Version.hpp"

namespace rtype {

    class ClientGameNetworkEntitySyncSystem : public ecs::ASystem {
    public:
        virtual const ecs::Version &getType() const override;
        virtual void tick(long deltatime) override;

    public:
        static const ecs::Version Version;

    private:
        static const std::map<int, int> _networkTypeToSpriteId;

    private:
        int getAssetIdFromNetworkType(int type);
    };
}

#endif //R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEM_HPP
