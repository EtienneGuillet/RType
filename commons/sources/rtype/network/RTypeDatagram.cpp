/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagram.cpp
*/

/* Created the 18/11/2019 at 13:11 by julian.frabel@epitech.eu */

#include "RTypeDatagram.hpp"

rtype::network::RTypeDatagram::RTypeDatagram()
    : Datagram()
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram &other)
    : Datagram(other)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram::Datagram &other)
    : Datagram(other)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram::HostInfos &destination)
    : Datagram(destination)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const void *data, size_t size)
    : Datagram(data, size)
{

}

rtype::network::RTypeDatagram::RTypeDatagram(const rtype::network::RTypeDatagram::HostInfos &destination,
                                             const void *data, size_t size)
    : Datagram(destination, data, size)
{

}

rtype::network::RTypeDatagram::~RTypeDatagram()
{

}

rtype::network::RTypeDatagram &rtype::network::RTypeDatagram::operator=(const rtype::network::RTypeDatagram &rhs)
{
    if (this == &rhs)
        return *this;
    return *this;
}

rtype::network::RTypeDatagram & rtype::network::RTypeDatagram::operator=(const rtype::network::RTypeDatagram::Datagram &rhs)
{
    if (this == &rhs)
        return *this;
    Datagram::operator=(rhs)
    return *this;
}
