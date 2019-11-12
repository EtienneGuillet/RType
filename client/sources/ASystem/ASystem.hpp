#ifndef _A_SYSTEM_HPP_
#define _A_SYSTEM_HPP_

#include "IWorld.hpp"
#include <iostream>
#include <vector>

class ASystem : public ISystem
{
public:
    virtual void tick(int deltatime) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::string getType() = 0;
    virtual bool isRunning() = 0;
    virtual setWorld(IWorld world) = 0;
    virtual std::vector<std::string> getRequiredComponents();
};

#endif /* _A_SYSTEM_HPP_ */
