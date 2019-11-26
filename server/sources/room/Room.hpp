/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Room.hpp
*/

/* Created the 26/11/2019 at 05:12 by julian.frabel@epitech.eu */

#ifndef R_TYPE_ROOM_HPP
#define R_TYPE_ROOM_HPP

#include <string>
#include <vector>
#include <functional>
#include "client/Client.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {
    /*!
     * @class Room
     * @brief A class that represent a room
     */
    class Room {
    public:
        /*!
         * @brief ctor
         */
        Room();
        /*!
         * @brief cpy ctor deleted
         * @param other the object to copy
         */
        Room(const Room &other) = delete;
        /*!
         * @brief dtor
         */
        ~Room();
        /*!
         * @brief Assignment operator deleted
         * @param rhs the object to assign to
         * @return *this
         */
        Room &operator=(const Room &rhs) = delete;

    public:
        const std::string &getName() const;
        void setName(const std::string &name);
        unsigned char getCapacity() const;
        void setCapacity(unsigned char capacity);
        unsigned char getSlotUsed() const;
        void setSlotUsed(unsigned char slotUsed);
        bool hasPassword() const;
        void setHasPassword(bool hasPassword);
        const std::string &getPassword() const;
        void setPassword(const std::string &password);
        bool isGameRunning() const;
        void setGameRunning(bool gameRunning);
        void addClient(Client &client);
        void removeClient(const Client &client);
        void applyToClients(std::function<void(Client &)> func);

    private:
        std::string _name; /*!< The room name */
        unsigned char _capacity; /*!< The room maximal capacity */
        unsigned char _slotUsed; /*!< The number of slots used */
        bool _hasPassword; /*!< Does this room have a password */
        std::string _password; /*!< A password */
        bool _gameRunning; /*!< Is the game currently running */
        std::vector<Client &> _clients; /*!< The connected clients to this room */
    };
}

#else

namespace rtype {
    class Room;
}

#endif //R_TYPE_ROOM_HPP
