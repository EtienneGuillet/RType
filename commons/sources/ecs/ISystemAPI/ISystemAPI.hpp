#ifndef _I_SYSTEM_API_HPP_
#define _I_SYSTEM_API_HPP_

#include <memory>
#include "ecs/Version/Version.hpp"
#include "ecs/ISystem/ISystem.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class ISystemAPI
     * @brief An interface used to create any type of systems.
     */
    class ISystemAPI {
    public:
        /*!
         * @brief dtor
         */
        virtual ~ISystemAPI() = default;

        /*!
         * @brief Get a version describing the system.
         * @return A version that can be created with this api.
         */
        [[nodiscard]] virtual const Version &getVersion() const = 0;

        /*!
         * @brief Create a new system.
         * @return A new system.
         */
        [[nodiscard]] virtual std::shared_ptr<ISystem> createNewSystem() const = 0;

    };
} /* ecs */

#endif /* _I_SYSTEM_API_HPP_ */
