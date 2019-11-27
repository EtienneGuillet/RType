#ifndef R_TYPE_ENTITIESSTATE_HPP
#define R_TYPE_ENTITIESSTATE_HPP

#include <map>
#include "maths/Vectors.hpp"

namespace rtype {

    class EntitiesState {

        public:

        EntitiesState();

        ~EntitiesState() = default;

        void setPos(std::uint32_t x, std::uint32_t y, std::uint32_t z);

        b12software::maths::Vector3D getPos() const;

        void setRot(std::uint32_t x, std::uint32_t y);

        b12software::maths::Vector2D getRot() const;

        void setScale(std::uint32_t x, std::uint32_t y);

        b12software::maths::Vector2D getScale() const;

        void setId(std::uint32_t id);

        int getId() const;

        void setType(std::uint32_t type);

        int getType() const;

        private:

        std::uint32_t _id;
        std::uint32_t _type;
        std::uint32_t _posX;
        std::uint32_t _posY;
        std::uint32_t _posZ;
        std::uint32_t _rotX;
        std::uint32_t _rotY;
        std::uint32_t _scaleX;
        std::uint32_t _scaleY;
    };
}

#endif //R_TYPE_ENTITIESSTATE_HPP
