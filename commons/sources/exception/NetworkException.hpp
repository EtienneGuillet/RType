/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** NetworkException.hpp
*/

/* Created the 25/09/2019 at 20:52 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_NETWORKEXCEPTION_HPP
#define B12NETWORKING_NETWORKEXCEPTION_HPP

#include "B12SoftwareException.hpp"

/*!
 * @namespace b12software
 * @brief Main namespace for all b12 software
 */
namespace b12software {

    /*!
     * @namespace b12software::network
     * @brief Main namespace for networking stuff
     */
    namespace exception {

        /*!
         * @class NetworkException
         * @brief The root class of all network exceptions
         */
        class NetworkException : public B12SoftwareException {
        public:
            /*!
             * @brief Ctor
             * @param what A message describing the exception
             * @param where A message describing the location of the exception
             */
            NetworkException(const std::string &what, const std::string &where): B12SoftwareException(what, where) {};
        };
    }
}

#endif //B12NETWORKING_NETWORKEXCEPTION_HPP
