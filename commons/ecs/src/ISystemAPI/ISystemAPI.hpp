#ifndef _I_SYSTEM_API_HPP_
#define _I_SYSTEM_API_HPP_

#include "ISystem.hpp"
#include "IECS.hpp"

namespace ECS {
    class ISystemAPI: public IECS
    {
    public:
        virtual ISystem create() = 0;
    };
} /* ECS */

#endif /* _I_SYSTEM_API_HPP_ */
