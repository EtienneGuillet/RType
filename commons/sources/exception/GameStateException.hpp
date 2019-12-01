/*
** EPITECH PROJECT, 2022
** GameStateException.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_GAMESTATEEXCEPTION_HPP
#define R_TYPE_GAMESTATEEXCEPTION_HPP

#include <exception>
#include <string>
#include "where.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
         * @class GameStateException
         * @brief A class representing a exception of the GameState and EntitiesState classes.
         */
    class GameStateException : public std::exception {

        public:

        /*!
         * @brief Ctor
         * @param what A message describing the exception
         * @param where A message describing the location of the exception
         */
        GameStateException(const std::string &what, const std::string &where): _what(what), _where(where) {};

        /*!
         * @brief dtor
         */
        ~GameStateException() override = default;

        /*!
         * @brief Get the message describing the exception
         * @return A message describing the exception
         */
        const char *what() const noexcept override { return _what.c_str(); };
        /*!
         * @brief Get a message describing the location of the exception
         * @return A message describing the location of the exception
         */
        const char *where() const noexcept { return _where.c_str(); };
        private:
        std::string _what; /*!< A message describing the exception */
        std::string _where; /*!< A message describing the location of the exception */

    };
}
#endif //R_TYPE_GAMESTATEEXCEPTION_HPP
