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
         * @brief Virtual dtor.
         */
        virtual ~IECS() = default;

        /*!
         * @brief Create a new IWorld and returns it.
         * @return The world created.
         */
        virtual std::shared_ptr<IWorld> createWorld() = 0;

        /*!
         * @brief Create a new IEntity and returns it.
         * @param version The entity created.
         * @return The entity created.
         */
        virtual std::shared_ptr<IEntity> createEntity(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the system.
         * @param version the system.
         * @return True if the system is known, false otherwise.
         */
        virtual bool knowSystem(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the entity.
         * @param version the entity.
         * @return True if the entity is known, false otherwise.
         */
        virtual bool knowEntity(const Version &version) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents systems.
         * @param versions The differents version to be verified.
         * @return True if all the systems are known, false otherwise.
         */
        virtual bool knowSystems(const std::vector<Version> &versions) = 0;

        /*!
         * @brief Return true or false whether the ecs have the differents entities.
         * @param versions The differents entities to be verified.
         * @return True if all the entities are known, flase otherwise.
         */
        virtual bool knowEntities(const std::vector<Version> &versions) = 0;

        /*!
         * @brief Make the ecs learn a new system.
         * @param api System API that needs to be learn by the ECS.
         */
        virtual void learnSystem(const std::shared_ptr<ISystemAPI> &api) = 0;

        /*!
         * @brief Make the ecs learn a new entity.
         * @param api Entity API that needs to be learn by the ECS.
         */
        virtual void learnEntity(const std::shared_ptr<IEntityAPI> &api) = 0;
        
        /*!
         * @brief Make the ecs forget the system.
         * @param version the system to be forget.
         * @return Shared pointer of the system's API just forgot.
         */
        virtual std::shared_ptr<ISystemAPI> forgetSystem(const Version &version) = 0;

        /*!
         * @brief Make the ecs forget the entity.
         * @param version the entity to be forget.
         * @return Shared pointer of the entity's API just forgot.
         */
        virtual std::shared_ptr<IEntity> forgetEntity(const Version &version) = 0;
    };
} /* ecs */

#endif /* _I_ECS_HPP_ */
