/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ECSException.hpp
*/

/* Created the 19/11/2019 at 21:41 by julian.frabel@epitech.eu */

#ifndef R_TYPE_ECSEXCEPTION_HPP
#define R_TYPE_ECSEXCEPTION_HPP

#include "exception/B12SoftwareException.hpp"

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class ECSException
     * @brief An exception from the ecs namespace
     */
    class ECSException : public b12software::exception::B12SoftwareException {
    public:
        /*!
         * @brief ctor
         * @param what error message
         * @param where  error location
         */
        ECSException(const std::string &what, const std::string &where): B12SoftwareException(what, where) {};
    };
}

#endif //R_TYPE_ECSEXCEPTION_HPP
