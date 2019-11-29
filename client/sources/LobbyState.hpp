/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** LobbyState.hpp
*/

/* Created the 29/11/2019 at 15:47 by julian.frabel@epitech.eu */

#ifndef R_TYPE_LOBBYSTATE_HPP
#define R_TYPE_LOBBYSTATE_HPP

#include <vector>
#include <string>

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {
    /*!
     * @class LobbyState
     * @brief A class that represent the state of the client in lobby
     */
    class LobbyState {
    public:
        /*!
         * @struct LobbyData
         * @brief A structure representing a lobby data
         */
        struct LobbyData {
            std::string name; /*!< The lobby name */
            std::string password; /*!< The lobby password */
            bool hasPassword; /*!< Has the lobby a password */
            int size; /*!< The lobby size */
            int nbPlayers; /*!< The number of players in the lobby */
        };
        static const LobbyData emptyLobby; /*!< An empty lobby */

    public:
        LobbyState();
        ~LobbyState();
        LobbyState(const LobbyState &other);
        LobbyState &operator=(const LobbyState &other);

    public:
        /*!
         * @brief Is the user currently in a lobby
         * @return true if the user is in a lobby false otherwise
         */
        bool isInLobby() const;
        /*!
         * @brief Get the current lobby data
         * @return the current lobby data
         */
        const LobbyData &getCurrentLobbyData() const;
        /*!
         * @brief Get the players currently in the lobby
         * @return the players names
         */
        const std::vector<std::string> &getPlayersInLobby() const;

        /*!
         * @brief Is the lobby currently updating
         * @return true if updating false otherwise
         */
        bool isUpdatingLobby() const;
        /*!
         * @brief Request a lobby update
         */
        void requestLobbyListUpdate();
        /*!
         * @brief Get a lobby list
         * @return the list of existing lobby
         */
        const std::vector<LobbyData> &getLobbyList() const;

        /*!
         * @brief Is currently creating a lobby
         * @return true if the lobby is beeing created
         */
        bool isCreatingLobby() const;
        /*!
         * @brief Create a lobby
         * @param name The name of the scene to create
         * @param password The password for the scene (empty if none)
         * @param maxSize the maximum number of player in the scene 1-4
         */
        void createLobby(const std::string &name, const std::string &password = "", int maxSize = 4);
        /*!
         * @brief Has the create lobby function failed
         * @return true if failure
         */
        bool hasFailToCreateLobby() const;
        /*!
         * @brief The error description for the failure
         * @return The error description
         */
        const std::string &failToJoinLobbyError() const;

        /*!
         * @brief Is currently joining a lobby
         * @return true if joining a lobby
         */
        bool isJoiningLobby() const;
        /*!
         * @brief Join a lobby
         * @param name the name of the room to join
         * @param password the password to use (empty if none)
         */
        void joinLobby(const std::string &name, const std::string &password = "");
        /*!
         * @brief Has the join failed
         * @return true if failure
         */
        bool hasFailToJoinLobby() const;
        /*!
         * @brief The error for the failure
         * @return the error
         */
        const std::string &failToCreateLobbyError() const;

        /*!
         * @brief Is quitting the lobby
         * @return true if currently quitting the lobby
         */
        bool isQuittingLobby() const;
        /*!
         * @brief try to quit the lobby
         */
        void quitLobby();
        /*!
         * @brief Has it fail to qui the lobby
         * @return true if a failure occurred false otherwise
         */
        bool hasFailToQuitLobby() const;
        /*!
         * @brief The error of the failure
         * @return the error
         */
        const std::string &failToQuitLobbyError() const;

    public:
        /*!
         * @brief Notify that the creation was successfull
         */
        void validateCreate();
        /*!
         * @brief Notify that the join was sucessfull
         * @param names names of the players in the room
         */
        void validateJoin(const std::vector<std::string> &names);
        /*!
         * @brief notify that quit was successfull
         */
        void validateQuit();
        /*!
         * @brief Invalidate the creation
         * @param error error that occurred
         */
        void invalidateCreate(const std::string &error);
        /*!
         * @brief Invalidate the join command
         * @param error the error that occurred
         */
        void invalidateJoin(const std::string &error);
        /*!
         * @brief Invalidate the quit
         * @param error the error that occured
         */
        void invalidateQuit(const std::string &error);

        /*!
         * @brief Add a player name to the lobby
         * @param name the name of the player that joined
         */
        void addToLobby(const std::string &name);
        /*!
         * @brief Notity that a player left
         * @param name the name of the player that left
         */
        void removeFromLobby(const std::string &name);

        /*!
         * @brief Set the lobbies available
         * @param lobbys the lobbies available
         */
        void setAvailableLobby(const std::vector<LobbyData> &lobbys);

        /*!
         * @brief Get the username
         * @return the username
         */
        const std::string &getUsername() const;
        /*!
         * @brief Set the username
         * @param username the username to use
         */
        void setUsername(const std::string &username);

    private:
        std::string _username; /*!< Name of the user */
        bool _inLobby; /*!< Is the client in lobby */
        bool _requestLobbyList; /*!< Should the network request lobby */
        bool _createLobby; /*!< Should the network request lobby create */
        std::string _failedToCreateLobbyError; /*!< Error of the create lobby */
        bool _joinLobby; /*!< Should the network request lobby join */
        std::string _failedToJoinLobbyError; /*!< Error of the join lobby */
        bool _quitLobby; /*!< Should the network request lobby quit */
        std::string _failedToQuitLobbyError; /*!< Error of the quit lobby */
        std::vector<LobbyData> _lobbyList; /*!< A list of available lobby */
        LobbyData _currentLobby; /*!< The current lobby of the user */
        std::vector<std::string> _playersName; /*!< Player name of players in the current lobby */
    };
}

#endif //R_TYPE_LOBBYSTATE_HPP
