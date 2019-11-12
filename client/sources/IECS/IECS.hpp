#ifndef _I_ECS_HPP_
#define _I_ECS_HPP_

#include "IWorld.hpp"
#include "IComponent.hpp"
#include "IEntity.hpp"
#include <iostream>

class IECS
{
public:
    virtual IWorld createWorld() = 0;
    virtual IComponent createComponent() = 0;
    virtual IEntity createEntity(std::string name) = 0;
    virtual todo know() = 0;
    virtual todo knows() = 0;
    virtual void learn(todo) = 0;
    virtual todo forget(todo) = 0;
};

#endif /* _I_ECS_HPP_ */
