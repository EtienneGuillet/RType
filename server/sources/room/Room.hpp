/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Room.hpp
*/

/* Created the 26/11/2019 at 05:12 by julian.frabel@epitech.eu */

#ifndef R_TYPE_ROOM_HPP
#define R_TYPE_ROOM_HPP

#include <atomic>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include "client/Client.hpp"
#include "network/udp/IUdpSocket.hpp"
#include "rtype/network/GameInfos.hpp"

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
         * @param libsFolder The folder containing entities and systems libs
         */
        Room(const std::string &libsFolder);
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
        bool shouldGameRun() const;

    public:
        /*!
         * @brief Start this room game
         */
        void startGame();
        /*!
         * @brief Sync the game state on the network if needed
         * @param socket the socket to send the datas with
         */
        void syncGame(std::weak_ptr<b12software::network::udp::IUdpSocket> socket);

        /*!
         * @brief Set the user with username inputs
         * @param username the username of the user
         * @param inputs the user inputs
         */
        void setUsernameInputs(const std::string &username, const rtype::network::RTypeDatagramAction &inputs);

    private:
        /*!
         * @brief End the room game
         */
        void endGame();

        /*!
         * @brief sync game on network
         */
        void syncGameOnNetwork(const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket);

        /*!
         * @brief Sync display and or living data
         * @param client the client to send to
         * @param pIdx the idx of the player
         * @param socket the socket to send from
         * @param living should sync living packets
         * @param display should sync display packets
         */
        void syncDisplayLiving(Client &client, const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket, bool living, bool display);

        /*!
         * @brief Sync the score
         * @param client the client to sync score to
         * @param socket the socket to send to
         */
        void syncScore(Client &client, const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket);

        /*!
         * @brief Sync the charge
         * @param client the client to sync to
         * @param pIdx the idx of the player
         * @param socket the socket to send on
         */
        void syncCharge(Client &client, const std::weak_ptr<b12software::network::udp::IUdpSocket>& socket);

    private:
        /*!
         * @brief The thread game function runned
         * @param infos the infos to sync on the network
         * @param libsFolder The folder containing entities and systems libs
         */
        static void gameThreadFunc(const std::atomic_bool &shouldGameBeRunning, std::atomic_bool &threadRunning, std::weak_ptr<GameInfos> infos, const std::string libsFolder);

    private:
        std::string _name; /*!< The room name */
        unsigned char _capacity; /*!< The room maximal capacity */
        unsigned char _slotUsed; /*!< The number of slots used */
        bool _hasPassword; /*!< Does this room have a password */
        std::string _password; /*!< A password */
        bool _gameRunning; /*!< Is the game currently running */
        std::vector<std::reference_wrapper<Client>> _clients; /*!< The connected clients to this room */

        std::atomic_bool _shouldGameBeRunning; /*!< Should the game be running for this room */
        std::shared_ptr<GameInfos> _gameInfos; /*!< This room game infos */
        std::map<std::string, int> _clientPlayerMap; /*!< Map linking a client to a player */
        std::atomic_bool _threadRunning; /*!< Is the thread running */
        std::unique_ptr<std::thread> _thread; /*!< The game thread */
        const std::string _libsFolder; /*< The path of the libraries folder */
    };
}

#else

namespace rtype {
    class Room;
}

#endif //R_TYPE_ROOM_HPP
