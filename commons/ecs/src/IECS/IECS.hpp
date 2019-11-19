#ifndef _I_ECS_HPP_
#define _I_ECS_HPP_

#include "IWorld.hpp"
#include "IComponent.hpp"
#include "IEntity.hpp"
#include "Version.hpp"
#include "IComponentAPI.hpp"
#include "IEntityAPI.hpp"
#include "ISystemAPI.hpp"
#include <iostream>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IECS
     * @brief An interface common to every ecs classes.
     */
    class IECS
    {
    public:

        /*!
         * @brief Create a new IWorld and returns it.
         */
        virtual IWorld createWorld() = 0;

        /*!
         * @brief Create a new IComponent and returns it.
         */
        virtual IComponent createComponent() = 0;

        /*!
         * @brief Create a new IEntity and returns it.
         */
        virtual IEntity createEntity(const std::string &name) = 0;

        /*!
         * @brief Return true or false whether the ecs have the system.
         */
        virtual bool knowSystem(const std::string &name) = 0;

        /*!
         * @brief Return true or false whether the ecs have the component.
         */
        virtual bool knowComponent(Version &name) = 0;

        /*!
         * @brief Return true or false whether the ecs have the entity.
         */
        virtual bool knowEntity(const std::string &name) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents systems.
         */
        virtual bool knowSystem(const std::vector<std::string> &apis) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents components.
         */
        virtual bool knowsComponents(const std::vector<Version> &apis) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents entities.
         */
        virtual bool knowsEntities(const std::vector<std::string> &apis) = 0;

        /*!
         * @brief Make the ecs learn a new system.
         */
        virtual void learnSystem(const std::string &type, const ISystemAPI &api) = 0;

        /*!
         * @brief Make the ecs learn a new component.
         */
        virtual void learnComponent(Version &version, const IComponentAPI &api) = 0;

        /*!
         * @brief Make the ecs learn a new entity.
         */
        virtual void learnEntity(const std::string &type, const IEntityAPI &api) = 0;

        /*!
         * @brief Make the ecs forget the system.
         */
        virtual T &forgetSystem(const std::string &type) = 0;

        /*!
         * @brief Make the ecs forget the component.
         */
        virtual T &forgetComponent(Version &version) = 0;

        /*!
         * @brief Make the ecs forget the entity.
         */
        virtual T &forgetEntity(const std::string &type) = 0;
    };
} /* ecs */

#endif /* _I_ECS_HPP_ */
