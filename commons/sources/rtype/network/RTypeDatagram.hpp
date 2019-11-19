/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagram.hpp
*/

/* Created the 18/11/2019 at 13:11 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAM_HPP
#define R_TYPE_RTYPEDATAGRAM_HPP

#include <string>
#include <vector>
#include "network/HostInfos.hpp"
#include "network/udp/Datagram.hpp"
#include "rtype/network/utils.hpp"
#include "rtype/network/RTypeDatagramType.hpp"
#include "rtype/network/RTypeDatagramRoom.hpp"
#include "rtype/network/RTypeDatagramScore.hpp"
#include "rtype/network/RTypeDatagramLiving.hpp"
#include "rtype/network/RTypeDatagramAction.hpp"
#include "rtype/network/RTypeDatagramDisplay.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @namespace rtype::network
     * @brief A namespace that contains network related classes for the rtype project
     */
    namespace network {

        /*!
         * @class RTypeDatagram
         * @brief A class that will implement the rfc 69420 about the rtype communication protocol
         */
        class RTypeDatagram : public b12software::network::udp::Datagram {
        public:
            using Datagram = b12software::network::udp::Datagram;
            using HostInfos = b12software::network::HostInfos;

        public:
            /*!
             * @brief ctor
             */
            RTypeDatagram();
            /*!
             * @brief cpy ctor
             * @param other The datagram to build from
             */
            RTypeDatagram(const RTypeDatagram &other);
            /*!
             * @brief build a RTypeDatagram from a b12 Datagram
             * @param other the datagram to build from
             */
            RTypeDatagram(const Datagram &other);
            /*!
             * @brief ctor
             * @param destination The destination to set this datagram to
             */
            explicit RTypeDatagram(const HostInfos &destination);
            /*!
             * @brief ctor
             * @param data The data to set this datagram to
             * @param size The size of the data
             */
            RTypeDatagram(const void *data, size_t size);
            /*!
             * @brief ctor
             * @param destination The destination to set this datagram to
             * @param data The data to set this datagram to
             * @param size The size of the data
             */
            RTypeDatagram(const HostInfos &destination, const void *data, size_t size);
            /*!
             * @brief dtor
             */
            ~RTypeDatagram() override;

            /*!
             * @brief Assign a rtype datagram to this datagram
             * @param rhs the datagram to assign
             * @return *this
             */
            RTypeDatagram &operator=(const RTypeDatagram &rhs);
            /*!
             * @brief Assign a b12 datagram to this datagram
             * @param rhs the datagram to assign
             * @return *this
             */
            RTypeDatagram &operator=(const Datagram &rhs) override;

            /*!
             * @brief Initialize this datagram to only contain an op code
             * @param type the op code to use
             */
            void initSingleOpCodeDatagram(RTypeDatagramType type);
            /*!
             * @brief Initialize this datagram to be a connect datagram
             * @param username The username to use (will be truncated if more that 10 chars)
             */
            void init100ConnectDatagram(const std::string &username);
            /*!
             * @brief Initialize a room list datagram
             * @param rooms The rooms to send
             */
            void init111RoomListDatagram(const std::vector<RTypeDatagramRoom> &rooms);
            /*!
             * @brief Initialize a create room datagram
             * @param room The room to create
             */
            void init112CreateRoomDatagram(const RTypeDatagramRoom &room);
            /*!
             * @brief Initialize a join room datagram
             * @param room The room to join
             */
            void init116JoinRoomDatagram(const RTypeDatagramRoom &room);
            /*!
             * @brief Initialize a joined room response datagram
             * @param users The users in this room
             */
            void init117RoomJoinedDatagram(const std::vector<std::string> &users);
            /*!
             * @brief Initialize a action datagram
             * @param action the action to send
             */
            void init200ActionDatagram(const RTypeDatagramAction &action);
            /*!
             * @brief Initialize a display datagram
             * @param entity The entity to display
             */
            void init210DisplayDatagram(const RTypeDatagramDisplay &entity);
            /*!
             * @brief Initialize a living datagram
             * @param data the data to send
             */
            void init220LivingDatagram(const RTypeDatagramLiving &data);
            /*!
             * @brief Initialize a charge datagram
             * @param charge The charge percentage
             */
            void init230ChargeDatagram(unsigned char charge);
            /*!
             * @brief Initialize a score datagram
             * @param score The game score
             */
            void init240ScoreDatagram(const RTypeDatagramScore &score);
            /*!
             * @brief Initialize a end game datagram
             * @param score The end game score
             */
            void init250EndGameDatagram(const RTypeDatagramScore &score);

            /*!
             * @brief Get the type of a datagram
             * @return The type of a datagram
             */
            unsigned short getType() const;

            /*!
             * @brief Extract this datagram to be a connect datagram
             * @param username The username to use (will be truncated if more that 10 chars)
             */
            void extract100ConnectDatagram(std::string &username);
            /*!
             * @brief Extract a room list datagram
             * @param rooms The rooms to send
             */
            void extract111RoomListDatagram(std::vector<RTypeDatagramRoom> &rooms);
            /*!
             * @brief Extract a create room datagram
             * @param room The room to create
             */
            void extract112CreateRoomDatagram(RTypeDatagramRoom &room);
            /*!
             * @brief Extract a join room datagram
             * @param room The room to join
             */
            void extract116JoinRoomDatagram(RTypeDatagramRoom &room);
            /*!
             * @brief Extract a joined room response datagram
             * @param users The users in this room
             */
            void extract117RoomJoinedDatagram(std::vector<std::string> &users);
            /*!
             * @brief Extract a action datagram
             * @param action the action to send
             */
            void extract200ActionDatagram(RTypeDatagramAction &action);
            /*!
             * @brief Extract a display datagram
             * @param entity The entity to display
             */
            void extract210DisplayDatagram(RTypeDatagramDisplay &entity);
            /*!
             * @brief Extract a living datagram
             * @param data the data to send
             */
            void extract220LivingDatagram(RTypeDatagramLiving &data);
            /*!
             * @brief Extract a charge datagram
             * @param charge The charge percentage
             */
            void extract230ChargeDatagram(unsigned char &charge);
            /*!
             * @brief Extract a score datagram
             * @param score The game score
             */
            void extract240ScoreDatagram(RTypeDatagramScore &score);
            /*!
             * @brief Extract a end game datagram
             * @param score The end game score
             */
            void extract250EndGameDatagram(RTypeDatagramScore &score);
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAM_HPP
