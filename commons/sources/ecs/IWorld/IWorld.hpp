#ifndef _I_WORLD_HPP_
#define _I_WORLD_HPP_

#include "IEntity.hpp"
#include "ISystem.hpp"
#include "Version.hpp"
#include <iostream>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IEntity
     * @brief An interface common to every worlds.
     */
    class IWorld
    {
    public:

        /*!
         * @brief Run all the system in the world.
         */
        virtual void tick(long deltatime) = 0;

        /*!
         * @brief Add a new entity to the world.
         */
        virtual void pushEntity(IEntity entity) = 0;

        /*!
         * @brief Remove a entity from the world.
         */
        virtual IEntity &popEntity(std::string type) = 0;

        /*!
         * @brief Return the entities that has the component asked as parameter.
         */
        virtual std::vector<IEntity> &getEntitiesWith(std::vector<Version> &versions) = 0;

        /*!
         * @brief Apply a rule to every entities that has the set of components given as parameter.
         */
        virtual void applyToEach(std::vector<Version> &version) = 0;

        /*!
         * @brief Add a new system to the world.
         */
        virtual void addSystem(ISystem system) = 0;

        /*!
         * @brief Remove a system from the world.
         */
        virtual void removeSystem(std::string type) = 0;

        /*!
         * @brief Return the system asked as a string parameter.
         */
        virtual ISystem &getSystem(std::string type) = 0;
    };
} /* ecs */

#endif /* _I_WORLD_HPP_ */
