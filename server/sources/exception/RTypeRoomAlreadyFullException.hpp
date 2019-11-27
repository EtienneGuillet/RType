/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeRoomAlreadyFullException.hpp
*/

/* Created the 26/11/2019 at 06:38 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEROOMALREADYFULLEXCEPTION_HPP
#define R_TYPE_RTYPEROOMALREADYFULLEXCEPTION_HPP

#include "RTypeServerException.hpp"

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
        class RTypeRoomAlreadyFullException : public RTypeServerException {
        public:
            /*!
             * @brief Ctor
             * @param what A message describing the exception
             * @param where A message describing the location of the exception
             */
            RTypeRoomAlreadyFullException(const std::string &what, const std::string &where): RTypeServerException(what, where) {};
        };
    }
}

#endif //R_TYPE_RTYPEROOMALREADYFULLEXCEPTION_HPP
