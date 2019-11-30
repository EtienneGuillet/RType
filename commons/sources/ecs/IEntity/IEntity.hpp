#ifndef _I_ENTITY_HPP_
#define _I_ENTITY_HPP_

#include "ecs/IComponent/IComponent.hpp"
#include <iostream>
#include <memory>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IEntity
     * @brief An interface common to every entities.
     */
    class IEntity {
    public:
        /*!
         * @brief dtor
         */
        virtual ~IEntity() = default;

        /*!
         * @brief Return the component asked as a string parameter.
         * @param componentType Version of the component asked.
         * @return Weak pointer of the component.
         */
        virtual std::weak_ptr<IComponent> getComponent(const Version &componentType) = 0;

        /*!
         * @brief Return the components asked as a string parameter.
         * @param componentTypes Version of the components asked.
         * @return vector of weak pointer of the components if all the components are found, and empty vector else.
         */
        virtual std::vector<std::weak_ptr<IComponent>> getComponents(const std::vector<Version> &componentTypes) = 0;

        /*!
         * @brief Return true or false whether the entity has the component or not.
         * @param componentType Version of the component to check.
         * @return True if the entity has the component, false otherwise.
         */
        virtual bool hasComponent(const Version &componentType) const = 0;

        /*!
         * @brief Return true or false whether the entity has all the components or not.
         * @param componentType Version of all the components to check.
         * @return True if the entity has all the components, false otherwise.
         */
        virtual bool hasComponents(const std::vector<Version> &componentTypes) = 0;

        /*!
         * @brief Return the id of the entity.
         * @return The id.
         */
        virtual int getID() const = 0;

        /*!
         * @brief Set the id of the entity.
         */
        virtual void setId(int id) = 0;

        /*!
         * @brief Return the name of the entity.
         * @return The name.
         */
        virtual const std::string &getName() const = 0;

        /*!
         * @brief Add a new component to the entity.
         * @param Component A shared pointer of the component to add to the entity.
         */
        virtual void addComponent(const std::shared_ptr<IComponent> &component) = 0;

        /*!
         * @brief Remove a component from the entity.
         * @param version the component to be removed.
         * @return Shared pointer of the component just removed.
         */
        virtual std::shared_ptr<IComponent> removeComponent(const Version &version) = 0;
    };
} /* ecs */

#else

namespace ecs {
    class IEntity;
}

#endif /* _I_ENTITY_HPP_ */
