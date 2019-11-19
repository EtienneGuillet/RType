#ifndef _A_SYSTEM_HPP_
#define _A_SYSTEM_HPP_

#include "ecs/IWorld/IWorld.hpp"
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
    class ASystem : public ISystem {
    public:

        /*!
         * @brief Ctor of the class ASystem.
         */
        ASystem();

        /*!
         * @brief Dtor of the class ASystem. Set _isRunning to false.
         */
        virtual ~ASystem() = default;

        /*!
         * @brief Return true or false whether the system is running or not.
         */
        virtual bool isRunning() const;

        /*!
         * @brief Start the system.
         */
        virtual void start();

        /*!
         * @brief Stop the system.
         */
        virtual void stop();

    private:

        bool _isRunning;
    };
} /* ecs */


#endif /* _A_SYSTEM_HPP_ */
