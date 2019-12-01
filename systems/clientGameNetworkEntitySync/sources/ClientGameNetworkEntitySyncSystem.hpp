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
#include "maths/Vectors.hpp"
#include "components/TransformComponent.hpp"
#include "ecs/ASystem/ASystem.hpp"
#include "ecs/Version/Version.hpp"

namespace rtype {

    class ClientGameNetworkEntitySyncSystem : public ecs::ASystem {
    public:
        virtual const ecs::Version &getType() const override;
        virtual void tick(long deltatime) override;
        void start() override;

    public:
        static const ecs::Version Version;

    private:
        static const std::map<int, int> _networkTypeToSpriteId;

    private:
        static float convertRange(float value, float oldRangeMin, float oldRangeMax, float newRangeMin, float newRangeMax);
        static sf::Vector3f mapPercentCoordinatesToPixelCoordianes(const b12software::maths::Vector3D &coords, int width, int height);
        static sf::Vector2f mapPercentCoordinatesToPixelCoordianes(const b12software::maths::Vector2D &coords, int width, int height);
        static b12software::maths::Vector3D mapPercentCoordinatesToPixelCoordianes(const sf::Vector3f &coords, int width, int height);
        static b12software::maths::Vector2D mapPercentCoordinatesToPixelCoordianes(const sf::Vector2f &coords, int width, int height);

    private:
        static int getAssetIdFromNetworkType(int type);
    };
}

#endif //R_TYPE_CLIENTGAMENETWORKENTITYSYNCSYSTEM_HPP
