/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** TransformNetworkLagCompensation.hpp
*/

/* Created the 01/12/2019 at 17:47 by julian.frabel@epitech.eu */

#ifndef R_TYPE_TRANSFORMNETWORKLAGCOMPENSATION_HPP
#define R_TYPE_TRANSFORMNETWORKLAGCOMPENSATION_HPP

#include "ecs/IComponent/AComponent.hpp"
#include "maths/Vectors.hpp"
#include <chrono>

namespace rtype {

    class TransformNetworkLagCompensation: public ecs::AComponent {
    public:
        static const ecs::Version Version;

    public:
        TransformNetworkLagCompensation();
        ~TransformNetworkLagCompensation() = default;
        TransformNetworkLagCompensation(const TransformNetworkLagCompensation &other) = default;
        TransformNetworkLagCompensation &operator=(const TransformNetworkLagCompensation &rhs) = default;

    public:
        const ecs::Version &getVersion() const override;

    public:
        const b12software::maths::Vector3D &getDirection() const;
        void setLastNetworkPos(const b12software::maths::Vector3D &pos);
        const b12software::maths::Vector3D &getLastNetworkPos() const;
        const b12software::maths::Vector3D &getPreviousNetworkPos() const;
        const std::chrono::high_resolution_clock::time_point &getLastUpdate() const;
        const std::chrono::high_resolution_clock::time_point &getPreviousUpdate() const;
        const std::chrono::milliseconds &getElapsed() const;

    private:
        int _hasEnougthValues;
        b12software::maths::Vector3D _lastNetworkPos;
        b12software::maths::Vector3D _previousNetworkPos;
        std::chrono::high_resolution_clock::time_point _lastTP;
        std::chrono::high_resolution_clock::time_point _previousTP;
        std::chrono::milliseconds _elapsed;
        b12software::maths::Vector3D _dir;
    };
}

#endif //R_TYPE_TRANSFORMNETWORKLAGCOMPENSATION_HPP
