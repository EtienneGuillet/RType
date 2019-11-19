#ifndef _I_COMPONENT_API_HPP_
#define _I_COMPONENT_API_HPP_

#include <memory>
#include "ecs/Version/Version.hpp"
#include "ecs/IComponent/IComponent.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IComponentAPI
     * @brief An interface used to create any type of component.
     */
    class IComponentAPI {
    public:
        /*!
         * @brief dtor
         */
        virtual ~IComponentAPI() = default;

        /*!
         * @brief Get a version describing the component
         * @return A version that can be created with this api
         */
        [[nodiscard]] virtual const Version &getVersion() const = 0;

        /*!
         * @brief Create a new component
         * @return A new component
         */
        [[nodiscard]] virtual std::shared_ptr<IComponent> createNewComponent() const = 0;
    };
} /* ecs */

#endif /* _I_COMPONENT_API_HPP_ */
