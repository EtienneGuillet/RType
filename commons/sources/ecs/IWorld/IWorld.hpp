#ifndef _I_WORLD_HPP_
#define _I_WORLD_HPP_

#include "ecs/IEntity/IEntity.hpp"
#include "ecs/ISystem/ISystem.hpp"
#include "ecs/Version/Version.hpp"
#include <iostream>
#include <functional>
#include <memory>

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
        virtual ~IWorld() = default;

        /*!
         * @brief Run all the system in the world.
         * @param deltatime the elapsed delta time as ms.
         */
        virtual void tick(long deltatime) = 0;

        /*!
         * @brief Add a new entity to the world.
         * @param entity the entity to add
         */
        virtual std::weak_ptr<IEntity> pushEntity(const std::shared_ptr<IEntity> &entity) = 0;

        /*!
         * @brief Remove a entity from the world.
         * @param id the entity id.
         * @return a shared ptr to the entity that as pop.
         */
        virtual std::shared_ptr<IEntity> popEntity(int id) = 0;

        /*!
         * @brief Return the entities that has the component asked as parameter.
         * @param components the components seached.
         * @return entities that matched this set of components.
         */
        [[nodiscard]] virtual std::vector<std::weak_ptr<IEntity>> getEntitiesWith(const std::vector<Version> &components) const = 0;

        /*!
         * @brief Return the entity that has a given id
         * @param id the id seached.
         * @return entity that match this is
         */
        [[nodiscard]] virtual std::weak_ptr<IEntity> getEntityById(int id) const = 0;

        /*!
         * @brief Apply a rule to every entities that has the set of components given as parameter.
         * @param components the set of components.
         * @param toApply the function to apply.
         */
        virtual void applyToEach(const std::vector<Version> &componentTypes, std::function<void (std::weak_ptr<IEntity>, std::vector<std::weak_ptr<IComponent>>)> toApply) = 0;

        /*!
         * @brief Add a new system to the world.
         * @param system the system to add.
         */
        virtual std::weak_ptr<ISystem> addSystem(const std::shared_ptr<ISystem> &system) = 0;

        /*!
         * @brief Remove a system from the world.
         * @param system the version of the system to remove.
         */
        virtual void removeSystem(const Version &system) = 0;

        /*!
         * @brief Return the system asked as a string parameter.
         * @param system the version of the system to remove.
         */
        virtual std::weak_ptr<ISystem> getSystem(const Version &system) = 0;
    };
} /* ecs */

#else

namespace ecs {
    class IWorld;
}

#endif /* _I_WORLD_HPP_ */
