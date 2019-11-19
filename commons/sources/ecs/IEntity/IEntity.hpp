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
         */
        virtual std::weak_ptr<IComponent> getComponent(const Version &componentType) = 0;

        /*!
         * @brief Return true or false whether the entity has the component or not.
         */
        virtual bool hasComponent(const Version &componentType) const = 0;

        /*!
         * @brief Return true or false whether the entity has all the components or not.
         */
        virtual bool hasComponents(const std::vector<Version> &componentTypes) = 0;

        /*!
         * @brief Return the id of the entity.
         */
        virtual int getID() const = 0;

        /*!
         * @brief Return the name of the entity.
         */
        virtual const std::string &getName() const = 0;

        /*!
         * @brief Add a new component to the entity.
         */
        virtual void addComponent(const std::shared_ptr<IComponent> &Component) = 0;

        /*!
         * @brief Remove a component from the entity.
         */
        virtual const std::shared_ptr<IComponent> &removeComponent(const Version &version) = 0;
    };
} /* ecs */

#else

namespace ecs {
    class IEntity;
}

#endif /* _I_ENTITY_HPP_ */
