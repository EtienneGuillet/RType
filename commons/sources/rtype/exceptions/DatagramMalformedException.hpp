/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DatagramMalformedException.hpp
*/

/* Created the 25/11/2019 at 12:10 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DATAGRAMMALFORMEDEXCEPTION_HPP
#define R_TYPE_DATAGRAMMALFORMEDEXCEPTION_HPP

#include "DatagramErrorException.hpp"

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
        class DatagramMalformedException : public DatagramErrorException {
        public:
            /*!
             * @brief Ctor
             * @param what A message describing the exception
             * @param where A message describing the location of the exception
             */
            DatagramMalformedException(const std::string &what, const std::string &where): DatagramErrorException(what, where) {};
        };
    }
}

#endif //R_TYPE_DATAGRAMMALFORMEDEXCEPTION_HPP
