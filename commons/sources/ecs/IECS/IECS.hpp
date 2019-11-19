#ifndef _I_ECS_HPP_
#define _I_ECS_HPP_

#include "../IWorld/IWorld.hpp"
#include "../IComponent/IComponent.hpp"
#include "../IEntity/IEntity.hpp"
#include "../IEntity/Version.hpp"
#include "../IComponentAPI/IComponentAPI.hpp"
#include "../IEntityAPI/IEntityAPI.hpp"
#include "../ISystemAPI/ISystemAPI.hpp"
#include <iostream>
#include <memory>

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
        virtual std::shared_ptr<IWorld> createWorld() = 0;

        /*!
         * @brief Create a new IComponent and returns it.
         */
        virtual std::shared_ptr<IComponent> createComponent(const Version &version) = 0;

        /*!
         * @brief Create a new IEntity and returns it.
         */
        virtual std::shared_ptr<IEntity> createEntity(onst Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the system.
         */
        virtual bool knowSystem(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the component.
         */
        virtual bool knowComponent(const Version &name) = 0;

        /*!
         * @brief Return true or false whether the ecs have the entity.
         */
        virtual bool knowEntity(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents systems.
         */
        virtual bool knowSystem(const std::vector<Version> &apis) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents components.
         */
        virtual bool knowsComponents(const std::vector<Version> &apis) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents entities.
         */
        virtual bool knowsEntities(const std::vector<Version> &apis) = 0;

        /*!
         * @brief Make the ecs learn a new system.
         */
        virtual void learnSystem(const Version &version, const std::shared_ptr<ISystemAPI> &api) = 0;

        /*!
         * @brief Make the ecs learn a new component.
         */
        virtual void learnComponent(const Version &version, const std::shared_ptr<IComponentAPI> &api) = 0;

        /*!
         * @brief Make the ecs learn a new entity.
         */
        virtual void learnEntity(const Version &version, const std::shared_ptr<IEntityAPI> &api) = 0;
        
        /*!
         * @brief Make the ecs forget the system.
         */
        virtual std::shared_ptr<ISystemAPI> &forgetSystem(const Version &version) = 0;

        /*!
         * @brief Make the ecs forget the component.
         */
        virtual std::shared_ptr<IComponentAPI> &forgetComponent(const Version &version) = 0;

        /*!
         * @brief Make the ecs forget the entity.
         */
        virtual std::shared_ptr<IEntity> &forgetEntity(const Version &version) = 0;
    };
} /* ecs */

#endif /* _I_ECS_HPP_ */
