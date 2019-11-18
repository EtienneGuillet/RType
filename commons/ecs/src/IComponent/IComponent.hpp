#ifndef _I_COMPONENT_HPP_
#define _I_COMPONENT_HPP_

#include "Version.hpp"
#include <iostream>

namespace ECS {
    class IComponent
    {
    public:
        virtual std::string getType() = 0;
        virtual Version getVersion() = 0;
        template <typename T> virtual T &getParam(std::string &type) = 0;
        template <typename T> virtual void setParam(std::string type, T &value) = 0;
    };
} /* ECS */

#endif /* _I_COMPONENT_HPP_ */
