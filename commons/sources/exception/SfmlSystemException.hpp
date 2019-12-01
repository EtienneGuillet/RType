/*
** EPITECH PROJECT, 2022
** SfmlSystemException.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_SFMLSYSTEMEXCEPTION_HPP
#define R_TYPE_SFMLSYSTEMEXCEPTION_HPP

#include "exception/B12SoftwareException.hpp"

/*!
 * @class SfmlSystemException
 * @brief An exception from the sfml system
 */
class SfmlSystemException : public b12software::exception::B12SoftwareException {
    public:
    /*!
     * @brief ctor
     * @param what error message
     * @param where  error location
     */
    SfmlSystemException(const std::string &what, const std::string &where): B12SoftwareException(what, where) {};
};

#endif //R_TYPE_SFMLSYSTEMEXCEPTION_HPP
