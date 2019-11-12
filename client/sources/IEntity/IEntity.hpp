#ifndef _I_ENTITY_HPP_
#define _I_ENTITY_HPP_

#include "IComponent.hpp"
#include <iostream>

class IEntity
{
public:
    virtual IComponent getComponent(std::string componentType) = 0;
    virtual bool hasComponent(std::string componentType) = 0;
    virtual bool hasComponents(std::vector<std::string> componentsType) = 0;
    virtual int getID() = 0;
    virtual std::string getName() = 0;
    virtual void addComponent(IComponent Component) = 0;
    virtual IComponent removeComponent(std::string type) = 0;
};

#endif /* _I_ENTITY_HPP_ */
