#ifndef _I_SYSTEM_API_HPP_
#define _I_SYSTEM_API_HPP_

#include "ISystem.hpp"
#include "IECS.hpp"

class ISystemAPI: public IECS
{
public:
    virtual ISystem create() = 0;
};

#endif /* _I_SYSTEM_API_HPP_ */
