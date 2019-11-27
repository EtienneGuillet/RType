/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeServerException.hpp
*/

/* Created the 21/11/2019 at 18:21 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPESERVEREXCEPTION_HPP
#define R_TYPE_RTYPESERVEREXCEPTION_HPP

#include "exception/B12SoftwareException.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @namespace rtype::exception
     * @brief Main namespace of exceptions in the rtype server
     */
    namespace exception {

        /*!
         * @class RTypeServerException
         * @brief Main exception of the rtype server
         */
        class RTypeServerException : public b12software::exception::B12SoftwareException {
        public:
            /*!
             * @brief Ctor
             * @param what A message describing the exception
             * @param where A message describing the location of the exception
             */
            RTypeServerException(const std::string &what, const std::string &where): B12SoftwareException(what, where) {};
        };
    }
}

#endif //R_TYPE_RTYPESERVEREXCEPTION_HPP
