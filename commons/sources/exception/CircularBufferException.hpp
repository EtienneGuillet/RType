/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** CircularBufferException.hpp
*/

/* Created the 08/08/2019 at 19:13 by julian.frabel@epitech.eu */

#ifndef CPP_B12SOFTWARE_CIRCULARBUFFEREXCEPTION_HPP
#define CPP_B12SOFTWARE_CIRCULARBUFFEREXCEPTION_HPP

#include "B12SoftwareException.hpp"

/*!
 * @namespace b12software
 * @brief Main namespace for all b12 software
 */
namespace b12software {

    /*!
     * @namespace b12software::exception
     * @brief Main namespace for b12software exceptions
     */
    namespace exception {

        /*!
         * @class CircularBufferException
         * @brief A class representing an exception in a circular buffer
         */
        class CircularBufferException : public B12SoftwareException {
        public:
            /*!
             * @brief Ctor
             * @param what A message describing the exception
             * @param where A message describing the location of the exception
             */
            CircularBufferException(const std::string &what, const std::string &where): B12SoftwareException(what, where) {};
        };
    }
}

#endif //CPP_B12SOFTWARE_CIRCULARBUFFEREXCEPTION_HPP
