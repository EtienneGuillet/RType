/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** Datagram.hpp
*/

/* Created the 24/09/2019 at 20:40 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_DATAGRAM_HPP
#define B12NETWORKING_DATAGRAM_HPP

#include "network/HostInfos.hpp"

namespace b12software::network {

    /*!
     * @namespace b12software::network::udp
     * @brief UDP related classes namespace
     */
    namespace udp {

        /*!
         * @class Datagram
         * @brief A datagram
         */
        class Datagram {
        public:
            /*!
             * @brief ctor
             */
            Datagram();
            /*!
             * @brief ctor
             * @param destination The destination to set this datagram to
             */
            explicit Datagram(const HostInfos &destination);
            /*!
             * @brief ctor
             * @param data The data to set this datagram to
             * @param size The size of the data
             */
            Datagram(const void *data, size_t size);
            /*!
             * @brief ctor
             * @param destination The destination to set this datagram to
             * @param data The data to set this datagram to
             * @param size The size of the data
             */
            Datagram(const HostInfos &destination, const void *data, size_t size);
            /*!
             * @brief ctor
             * @param other The datagram to copy
             */
            Datagram(const Datagram &other);
            /*!
             * @brief dtor
             */
            virtual ~Datagram();

            /*!
             * @brief Assignment operator
             * @param rhs The datagram to copy
             * @return this datagram
             */
            virtual Datagram &operator=(const Datagram &rhs);

            /*!
             * @brief Set the data of the datagram
             * @param data The data to set to
             * @param size The size of the data
             */
            void setData(const void *data, size_t size);
            /*!
             * @brief Set the destination of this datagram
             * @param infos The destination to send to
             */
            void setDestination(const HostInfos &infos);

            /*!
             * @brief Get the data of this datagram
             * @return The data contained inside this datagram
             */
            const void *getData() const;
            /*!
             * @brief Get the size of the data contained inside the datagram
             * @return The size of the data
             */
            size_t getDatagramSize() const;
            /*!
             * @brief Get the host information (sender/destination)
             * @return The host information of the sender / destination
             */
            const HostInfos &getHostInfos() const;

            /*!
             * @brief Get if the datagram is complete
             * @return true if the datagram is valid false otherwise
             *
             * To be valid a datagram must have an host, some data and a size
             */
            bool isValid() const;
            /*!
             * @brief Clear all the data of the datagram
             */
            void clear();

        protected:
            using byte = unsigned char;

            byte *_data; /*!< The data of the datagram */
            size_t _size; /*!< The size of this datagram data */
            HostInfos _infos; /*!< Information about the sender/destination of tis datagram */
        };
    }
}

#endif //B12NETWORKING_DATAGRAM_HPP
