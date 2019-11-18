#ifndef _I_WORLD_HPP_
#define _I_WORLD_HPP_

#include "IEntity.hpp"
#include "ISystem.hpp"
#include <iostream>

namespace ecs {
    class IWorld
    {
    public:
        virtual void tick(long deltatime) = 0;
        virtual void pushEntity(IEntity entity) = 0;
        virtual IEntity popEntity(std::string type) = 0;
        virtual IEntity getEntityWith(std::string componentType) = 0;
        virtual void applyToEach(std::string type) = 0;
        virtual void addSystem(ISystem system) = 0;
        virtual ISystem removeSystem(std::string type) = 0;
        virtual ISystem getSystem(std::string type) = 0;
    };
} /* ecs */

#endif /* _I_WORLD_HPP_ */
