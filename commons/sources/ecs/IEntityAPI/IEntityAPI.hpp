#ifndef _I_ENTITY_API_HPP_
#define _I_ENTITY_API_HPP_

#include <memory>
#include "ecs/Version/Version.hpp"
#include "ecs/IEntity/IEntity.hpp"
#include "ecs/IWorld/IWorld.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IEntityAPI
     * @brief An interface used to create any type of entity.
     */
    class IEntityAPI {
    public:
        /*!
         * @brief dtor
         */
        virtual ~IEntityAPI() = default;

        /*!
         * @brief Get a version describing the entity.
         * @return A version that can be created with this api.
         */
        [[nodiscard]] virtual const Version &getVersion() const = 0;

        /*!
         * @brief Create a new entity.
         * @return A new entity.
         */
        [[nodiscard]] virtual std::shared_ptr<IEntity> createNewEntity() const = 0;
    };
} /* ecs */

#endif /* _I_ENTITY_API_HPP_ */
