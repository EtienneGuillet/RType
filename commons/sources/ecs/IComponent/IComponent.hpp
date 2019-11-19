#ifndef _I_COMPONENT_HPP_
#define _I_COMPONENT_HPP_

#include "ecs/Version/Version.hpp"
#include <iostream>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IComponent
     * @brief An interface that is common to all components in the ecs.
     */
    class IComponent
    {
    public:

        /*!
         * @brief Get the parameter value, the parameter speed would return a int or a float for instance.
         */
        template <typename T> virtual T &getParam(const std::string &type) const = 0;

        /*!
         * @brief Assign a new value to a parameter.
         */
        template <typename T> virtual void setParam(const std::string &type, T &value) = 0;
    };
} /* ecs */

#endif /* _I_COMPONENT_HPP_ */
