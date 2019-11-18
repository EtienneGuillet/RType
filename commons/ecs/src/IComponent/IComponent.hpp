#ifndef _I_COMPONENT_HPP_
#define _I_COMPONENT_HPP_

#include "Version.hpp"
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
         * @brief Return the type of the component in string format.
         */
        virtual std::string getType() = 0;

        /*!
         * @brief Return the version of the component.
         */
        virtual Version getVersion() = 0;

        /*!
         * @brief Get the parameter value, the parameter speed would return a int or a float for instance.
         */
        template <typename T> virtual T &getParam(std::string &type) = 0;

        /*!
         * @brief Assign a new value to a parameter.
         */
        template <typename T> virtual void setParam(std::string type, T &value) = 0;
    };
} /* ecs */

#endif /* _I_COMPONENT_HPP_ */