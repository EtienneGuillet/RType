#ifndef _I_WORLD_HPP_
#define _I_WORLD_HPP_

#include "ecs/IEntity/IEntity.hpp"
#include "ecs/ISystem/ISystem.hpp"
#include "ecs/Version/Version.hpp"
#include <iostream>
#include <functional>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IEntity
     * @brief An interface common to every worlds.
     */
    class IWorld {
    public:

        /*!
         * @brief Dtor of the class IWord.
         */
        virtual ~IWorld() = 0;

        /*!
         * @brief Run all the system in the world.
         */
        virtual void tick(long deltatime) = 0;

        /*!
         * @brief Add a new entity to the world.
         */
        virtual void pushEntity(std::shared_ptr<IEntity> entity) = 0;

        /*!
         * @brief Remove a entity from the world.
         */
        virtual IEntity &popEntity(std::shared_ptr<const Version &> version) = 0;

        /*!
         * @brief Return the entities that has the component asked as parameter.
         */
        [[nodiscard]] virtual std::vector<IEntity> &getEntitiesWith(const std::vector<std::weak_ptr<IEntity>> &entity) const = 0;

        /*!
         * @brief Apply a rule to every entities that has the set of components given as parameter.
         */
        virtual void applyToEach(const std::vector<Version> &versions, const std::function<void (std::weak_ptr<IEntity>, std::vector<std::weak_ptr<IComponent>>)> &toApply) = 0;

        /*!
         * @brief Add a new system to the world.
         */
        virtual void addSystem(std::shared_ptr<ISystem> system) = 0;

        /*!
         * @brief Remove a system from the world.
         */
        virtual void removeSystem(const Version &version) = 0;

        /*!
         * @brief Return the system asked as a string parameter.
         */
        virtual std::weak_ptr<ISystem> getSystem(const Version &version) = 0;
    };
} /* ecs */

#else

namespace ecs {
    class IWorld;
}

#endif /* _I_WORLD_HPP_ */
