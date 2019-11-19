/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PacketErrorException.hpp
*/

/* Created the 18/11/2019 at 17:58 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DATAGRAMERROREXCEPTION_HPP
#define R_TYPE_DATAGRAMERROREXCEPTION_HPP

#include "exception/B12SoftwareException.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @namespace rtype::exceptions
     * @brief a namespace for exceptions
     */
    namespace exceptions {
        /*!
         * @class DatagramErrorException
         * @brief A class that represent a datagram exception (forging an invalid packet)
         */
        class DatagramErrorException : public b12software::exception::B12SoftwareException {
        public:
            /*!
             * @brief Ctor
             * @param what A message describing the exception
             * @param where A message describing the location of the exception
             */
            DatagramErrorException(const std::string &what, const std::string &where): B12SoftwareException(what, where) {};
        };
    }
}

#endif //R_TYPE_DATAGRAMERROREXCEPTION_HPP
