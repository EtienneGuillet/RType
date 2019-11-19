#ifndef _I_ENTITY_HPP_
#define _I_ENTITY_HPP_

#include "IComponent.hpp"
#include <iostream>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IEntity
     * @brief An interface common to every entities.
     */
    class IEntity
    {
    public:

        /*!
         * @brief Return the component asked as a string parameter.
         */
        virtual IComponent getComponent(const std::string &componentType) = 0;

        /*!
         * @brief Return true or false whether the entity has the component or not.
         */
        virtual bool hasComponent(const std::string &componentType, Version &version) = 0;

        /*!
         * @brief Return true or false whether the entity has all the components or not.
         */
        virtual bool hasComponents(std::vector<Version> componentsType) = 0;

        /*!
         * @brief Return the id of the entity.
         */
        virtual int getID() = 0;

        /*!
         * @brief Return the name of the entity.
         */
        virtual std::string getName() = 0;

        /*!
         * @brief Add a new component to the entity.
         */
        virtual void addComponent(IComponent &Component) = 0;

        /*!
         * @brief Remove a component from the entity.
         */
        virtual IComponent removeComponent(const std::string &type) = 0;
    };
} /* ecs */

#endif /* _I_ENTITY_HPP_ */
