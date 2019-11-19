#ifndef _I_SYSTEM_HPP_
#define _I_SYSTEM_HPP_

#include "ecs/IWorld/IWorld.hpp"
#include "ecs/Version/Version.hpp"
#include <iostream>
#include <vector>
#include <memory>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class ISystem
     * @brief An interface common to every systems.
     */
    class ISystem
    {
    public:
        /*!
         * @brief dtor
         */
        virtual ~ISystem() = default;

        /*!
         * @brief Run the system main functionality.
         * @param deltatime the elapsed delta time as ms.
         */
        virtual void tick(long deltatime) = 0;

        /*!
         * @brief Allow the system to execute.
         */
        virtual void start() = 0;

        /*!
         * @brief Forbid the system ability to execute.
         */
        virtual void stop() = 0;

        /*!
         * @brief Return the type of the entity as a Version object.
         * @return The Version object.
         */
        virtual const Version &getType() const = 0;

        /*!
         * @brief Return true or false whether the system is running or not.
         * @return True if running, false otherwise.
         */
        virtual bool isRunning() const = 0;

        /*!
         * @brief Set the world where the system is executed.
         * @param Weak pointer of the world to be assigned.
         */
        virtual void setWorld(const std::weak_ptr<IWorld> &world) = 0;
    };
} /* ecs */

#else

namespace ecs {
    class ISystem;
}

#endif /* _I_SYSTEM_HPP_ */
