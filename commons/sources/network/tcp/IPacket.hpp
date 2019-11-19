/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** IPacket.hpp
*/

/* Created the 25/09/2019 at 14:46 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_IPACKET_HPP
#define B12NETWORKING_IPACKET_HPP

#include <string>

namespace b12software::network {

    /*!
     * @namespace b12software::network::tcp
     * @brief TCP related classes namespace
     */
    namespace tcp {

        /*!
         * @class IPacket
         * @brief An interface representing a network packet
         */
        class IPacket {
        public:
            /*!
             * @brief dtor
             */
            virtual ~IPacket() = default;

            /*!
             * @brief Get the size of this packet
             * @return The size of the data contained in this packet
             */
            virtual size_t getSize() const = 0;
            /*!
             * @brief Get the data of the packet
             * @return The data contained in this packet
             */
            virtual const void *getData() const = 0;
            /*!
             * @brief Set the data of the packet
             * @param data The data to set
             * @param size The size of the data
             * @return The size of the data that was taken in the packet
             */
            virtual size_t setData(const void *data, size_t size) = 0;
            /*!
             * @brief Clear a given packet
             */
            virtual void clear() = 0;
            /*!
             * @brief Get if a packet is valid and can be used
             * @return true if the packet can be used false otherwise
             */
            virtual bool isValid() const = 0;
        };
    }
}

#endif //B12NETWORKING_IPACKET_HPP
