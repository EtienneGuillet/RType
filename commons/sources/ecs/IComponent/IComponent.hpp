#ifndef _I_COMPONENT_HPP_
#define _I_COMPONENT_HPP_

#include "ecs/Version/Version.hpp"
#include "ecs/IEntity/IEntity.hpp"
#include <iostream>
#include <memory>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IComponent
     * @brief An interface that is common to all components in the ecs.
     */
    class IComponent {
    public:

        /*!
         * @brief Dtor of the class IComponent.
         */
        virtual ~IComponent() = default;

        /*!
         * @brief Set the parent entity.
         * @param entity The entity to set.
         */
        virtual void setEntity(const std::weak_ptr<IEntity> &entity) = 0;

        /*!
         * @brief Get the parent entity.
         * @return The parent entity.
         */
        virtual std::weak_ptr<IEntity> getEntity() const = 0;

        /*!
         * @brief Get a component version
         * @return the Version asked.
         */
        virtual const Version &getVersion() const = 0;
    };
} /* ecs */

#else

namespace ecs {
    class IComponent;
}

#endif /* _I_COMPONENT_HPP_ */
