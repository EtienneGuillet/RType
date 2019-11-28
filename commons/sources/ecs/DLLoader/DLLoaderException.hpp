/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** DLLoaderException.hpp
*/

/* Created the 19/11/2019 at 15:33 by julian.frabel@epitech.eu */

#ifndef R_TYPE_DLLOADEREXCEPTION_HPP
#define R_TYPE_DLLOADEREXCEPTION_HPP

#include <exception>
#include <string>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class DLLoaderException
     * @brief An exception throwed when the loader has a problem
     */
    class DLLoaderException : public std::exception {
    public:
        /*!
         * @brief ctor
         * @param msg A message describing the error
         * @param where Information on where the error was throwed
         */
        DLLoaderException(const std::string &msg, const std::string &where)
            : _what(msg), _where(where)
        {};

        /*!
         * @brief Return the error message
         * @return An error describing the message
         */
        const char *what() const noexcept override
        {
            return _what.c_str();
        }

        /*!
         * @brief Return the error location
         * @return A string describing the location
         */
        const char *where() const noexcept
        {
            return _where.c_str();
        }

    private:
        std::string _what; /*!< The error message */
        std::string _where; /*!< The error location */
    };
}

#endif //R_TYPE_DLLOADEREXCEPTION_HPP
