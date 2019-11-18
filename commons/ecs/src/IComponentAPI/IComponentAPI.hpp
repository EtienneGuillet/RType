#ifndef _I_COMPONENT_API_HPP_
#define _I_COMPONENT_API_HPP_

#include "IECS.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IComponentAPI
     * @brief An interface used to create any type of component.
     */
    class IComponentAPI: public IECS
    {
    public:
    };
} /* ecs */

#endif /* _I_COMPONENT_API_HPP_ */
