#ifndef _I_ENTITY_HPP_
#define _I_ENTITY_HPP_

#include "IComponent.hpp"
#include <iostream>

namespace ECS {
    class IEntity
    {
    public:
        virtual IComponent getComponent(std::string componentType) = 0;
        virtual bool hasComponent(std::string componentType, Version &version) = 0;
        virtual bool hasComponents(std::vector<todoClassVersionType> componentsType) = 0;
        virtual int getID() = 0;
        virtual std::string getName() = 0;
        virtual void addComponent(IComponent Component) = 0;
        virtual IComponent removeComponent(std::string type) = 0;
    };
} /* ECS */

#endif /* _I_ENTITY_HPP_ */
