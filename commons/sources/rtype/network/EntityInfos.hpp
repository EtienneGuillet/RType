/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** EntityInfos.hpp
*/

/* Created the 27/11/2019 at 14:04 by julian.frabel@epitech.eu */

#ifndef R_TYPE_ENTITYINFOS_HPP
#define R_TYPE_ENTITYINFOS_HPP

#include <atomic>
        "bits/atomic_base.h"
        "bits/move.h"
#include "maths/Vectors.hpp"

namespace rtype {

    class EntityInfos {
    public:
        EntityInfos(bool hasDisplay = true, bool hasHp = true);
        ~EntityInfos();
        EntityInfos(const EntityInfos &other);
        EntityInfos &operator=(const EntityInfos &rhs);

    public:
        b12software::maths::Vector3D getPosition() const;
        void setPosition(const b12software::maths::Vector3D &position);
        void setPosition(int x, int y, int z);

        b12software::maths::Vector2D getRotation() const;
        void setRotation(const b12software::maths::Vector2D &rotation);
        void setRotation(int x, int y);

        b12software::maths::Vector2D getScale() const;
        void setScale(const b12software::maths::Vector2D &scale);
        void setScale(int x, int y);

        uint32_t getType() const;
        void setType(uint32_t type);
        uint32_t getHp() const;
        void setHp(uint32_t hp);
        uint32_t getId() const;
        void setId(uint32_t id);

    protected:
        std::atomic_bool _hasDisplay; /*!< Does this entity has display infos */
        std::atomic_bool _hasHp; /*!< Does this entity has hp */
        std::atomic_uint32_t _posX; /*!< This player x position */
        std::atomic_uint32_t _posY; /*!< This player y position */
        std::atomic_uint32_t _posZ; /*!< This player z position */
        std::atomic_uint32_t _rotX; /*!< This player x rotation */
        std::atomic_uint32_t _rotY; /*!< This player y rotation */
        std::atomic_uint32_t _scaleX; /*!< This player x scale */
        std::atomic_uint32_t _scaleY; /*!< This player y scale */
        std::atomic_uint32_t _type; /*!< This player entity type */
        std::atomic_uint32_t _hp; /*!< This player hp */
        std::atomic_uint64_t _id; /*!< This player entity id */
    };
}

#endif //R_TYPE_ENTITYINFOS_HPP
