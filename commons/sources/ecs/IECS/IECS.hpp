#ifndef _I_ECS_HPP_
#define _I_ECS_HPP_

#include "ecs/IWorld/IWorld.hpp"
#include "ecs/IComponent/IComponent.hpp"
#include "ecs/IEntity/IEntity.hpp"
#include "ecs/Version/Version.hpp"
#include "ecs/IEntityAPI/IEntityAPI.hpp"
#include "ecs/ISystemAPI/ISystemAPI.hpp"
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
    class IECS {
    public:

        /*!
         * @brief virtual dtor.
         */
        virtual ~IECS() = default;

        /*!
         * @brief Create a new IWorld and returns it.
         */
        virtual std::shared_ptr<IWorld> createWorld() = 0;

        /*!
         * @brief Create a new IEntity and returns it.
         */
        virtual std::shared_ptr<IEntity> createEntity(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the system.
         */
        virtual bool knowSystem(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the entity.
         */
        virtual bool knowEntity(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents systems.
         */
        virtual bool knowSystems(const std::vector<Version> &versions) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents entities.
         */
        virtual bool knowEntities(const std::vector<Version> &versions) = 0;

        /*!
         * @brief Make the ecs learn a new system.
         */
        virtual void learnSystem(const std::shared_ptr<ISystemAPI> &api) = 0;

        /*!
         * @brief Make the ecs learn a new entity.
         */
        virtual void learnEntity(const std::shared_ptr<IEntityAPI> &api) = 0;
        
        /*!
         * @brief Make the ecs forget the system.
         */
        virtual std::shared_ptr<ISystemAPI> &forgetSystem(const Version &version) = 0;

        /*!
         * @brief Make the ecs forget the entity.
         */
        virtual std::shared_ptr<IEntity> &forgetEntity(const Version &version) = 0;
    };
} /* ecs */

#endif /* _I_ECS_HPP_ */
