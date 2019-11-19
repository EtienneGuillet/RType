#ifndef _I_SYSTEM_HPP_
#define _I_SYSTEM_HPP_

#include "../IWorld/IWorld.hpp"
#include "../Version/Version.hpp"
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
         * @brief Run the system main functionality.
         */
        virtual void tick(long deltatime) = 0;

        /*!
         * @brief Allow the system to execute.
         */
        virtual void start() = 0;

        /*!
         * @brief Forbide the system ability to execute.
         */
        virtual void stop() = 0;

        /*!
         * @brief Return the type of the entity.
         */
        virtual const Version &getType() const = 0;

        /*!
         * @brief Return true or false whether the system is running or not.
         */
        virtual bool isRunning() const = 0;

        /*!
         * @brief Set the world where the system is executed.
         */
        virtual setWorld(const std::weak_ptr<IWorld> &world) = 0;

        /*!
         * @brief Return a vector of string describing every components needed.
         */
        virtual std::vector<Version> getRequiredComponents() = 0;
    };
} /* ecs */

#endif /* _I_SYSTEM_HPP_ */
