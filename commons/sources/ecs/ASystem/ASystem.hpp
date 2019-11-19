#ifndef _A_SYSTEM_HPP_
#define _A_SYSTEM_HPP_

#include "IWorld.hpp"
#include <iostream>
#include <vector>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class ASystem
     * @brief An abstract class that describe default behavior of any system.
     */
    class ASystem : public ISystem
    {
    public:

        virtual ~ASystem() = default;
        /*!
         * @brief Return true or false whether the system is running or not.
         */
        virtual bool isRunning();

        /*!
         * @brief Start the system.
         */
        virtual void start();

        /*!
         * @brief Stop the system.
         */
        virtual void stop();

    private:

        bool isRunning = false;
    };
} /* ecs */


#endif /* _A_SYSTEM_HPP_ */
