#ifndef _I_ECS_HPP_
#define _I_ECS_HPP_

#include "IWorld.hpp"
#include "IComponent.hpp"
#include "IEntity.hpp"
#include <iostream>

namespace ECS {
    class IECS
    {
    public:
        virtual IWorld createWorld() = 0;
        virtual IComponent createComponent() = 0;
        virtual IEntity createEntity(std::string name) = 0;
        virtual bool know(const std::string &name) = 0;
        virtual bool knows(templateVariadique) = 0;
        virtual void learn(const std::string &type, todo) = 0;
        virtual todo forget(const std::string &type, Version &version) = 0;
    };
} /* ECS */

#endif /* _I_ECS_HPP_ */
