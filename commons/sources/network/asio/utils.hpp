/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** utils.hpp
*/

/* Created the 15/11/2019 at 20:20 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_UTILS_HPP
#define B12NETWORKING_UTILS_HPP

#include <boost/asio.hpp>

template<typename T>
boost::shared_ptr<T> make_shared_ptr(std::shared_ptr<T>& ptr)
{
    return boost::shared_ptr<T>(ptr.get(), [ptr](T*) mutable {ptr.reset();});
}

template<typename T>
std::shared_ptr<T> make_shared_ptr(boost::shared_ptr<T>& ptr)
{
    return std::shared_ptr<T>(ptr.get(), [ptr](T*) mutable {ptr.reset();});
}

#endif //B12NETWORKING_UTILS_HPP
