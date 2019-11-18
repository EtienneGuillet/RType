#ifndef _I_SYSTEM_HPP_
#define _I_SYSTEM_HPP_

#include <iostream>
#include <vector>

namespace ecs {
    class ISystem
    {
    public:
        virtual void tick(long deltatime) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual std::string getType() = 0;
        virtual bool isRunning() = 0;
        virtual setWorld(IWorld world) = 0;
        virtual std::vector<std::string> getRequiredComponents() = 0;
    };
} /* ecs */

#endif /* _I_SYSTEM_HPP_ */
