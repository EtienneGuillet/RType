#ifndef _I_SYSTEM_API_HPP_
#define _I_SYSTEM_API_HPP_

#include "ISystem.hpp"
#include "IECS.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {
    class ISystemAPI: public IECS
    {
    public:
        virtual ISystem create() = 0;
    };
} /* ecs */

#endif /* _I_SYSTEM_API_HPP_ */
