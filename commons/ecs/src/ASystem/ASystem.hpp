#ifndef _A_SYSTEM_HPP_
#define _A_SYSTEM_HPP_

#include "IWorld.hpp"
#include <iostream>
#include <vector>

namespace ecs {
    class ASystem : public ISystem
    {
    public:
        virtual bool isRunning() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
} /* ecs */


#endif /* _A_SYSTEM_HPP_ */
