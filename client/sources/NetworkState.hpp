/*
** EPITECH PROJECT, 2022
** NetworkState.hpp
** File description:
** Created by tpautier,
*/

#ifndef R_TYPE_NETWORKSTATE_HPP
#define R_TYPE_NETWORKSTATE_HPP

#include "EntitiesState.hpp"
#include "LobbyState.hpp"
#include <vector>
#include <algorithm>

/*!
 * @enum NetworkStateKeys
 * @brief Enum representing the
 */
enum NetworkStateKeys {
    Z,
    Q,
    S,
    D,
    SPACE,
    ESCAPE,
    ENTER
};

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class GameState
     * @brief Used to store information of all the entities for graphical and network purpose.
     */
    class NetworkState {

        public:

        /*!
         * @brief Ctor.
         */
        NetworkState();

        /*!
         * @brief Dtor.
         */
        ~NetworkState() = default;

        /*!
         * @brief Add an entity to the vector of entities.
         * @param the entity to add.
         */
        void addEntity(const rtype::EntitiesState &entity);

        /*!
         * @brief Remove an entity to the vector of entities.
         * @param the id of the entity to remove.
         */
        void removeEntity(std::uint32_t id);

        /*!
         * @brief Get a entity.
         * @param id the id of the entity asked.
         * @return the entity found.
         */
        rtype::EntitiesState &getEntity(std::uint32_t id);

        /*!
         * @brief Get all the entities stored.
         * @return The vector of all the entities stored.
         */
        std::vector<rtype::EntitiesState> &getEntities();

        /*!
         * @brief Get a vector of entities that as the ids specified.
         * @param ids The ids of the entities wanted.
         * @return A copied vector of the entities found with the ids specified.
         */
        std::vector<rtype::EntitiesState> getEntities(const std::vector<std::uint32_t> &ids);

        /*
         * @brief Sort the vector of entities by there Position in Z axe.
         */
        void sortByZindex();

        /*!
         * @brief Set the inputs of the client.
         * @param A map of key and a bool, true or false whether the input is held or not.
         */
        void setInputs(const std::map<NetworkStateKeys, bool> &keys);

        /*!
         * @brief Get the inputs of the client.
         * @return A map of key and a bool, true or false whether the input is held or not.
         */
        const std::map<NetworkStateKeys, bool> &getInputs();

        /*!
         * @brief Set the state of a key
         * @param key the key
         * @param state the new state
         */
        void setInput(NetworkStateKeys key, bool state);

        /*!
         * @brief Set the charge
         * @param charge the new charge
         */
        void setCharge(uint8_t charge);

        /*!
         * @brief Get the charge
         * @return the charge
         */
        uint8_t getCharge() const;

        /*!
         * @brief get the lobby state
         * @return the state
         */
        rtype::LobbyState &getLobbyState();

        /*!
         * @brief Get the current server host
         * @return the host used
         */
        const std::string &getServerHost() const;
        /*!
         * @brief set the server host
         * @return the host
         */
        void setServerHost(const std::string &serverHost);
        /*!
         * @brief Get the server port
         * @return the server port
         */
        unsigned short getServerPort() const;
        /*!
         * @brief Set the server port
         * @return serverPort the server port
         */
        void setServerPort(unsigned short serverPort);

        /*!
         * @brief get if the server info changed
         * @return true if the infos changed false otherwise
         */
        bool hasServerInfoChanged();

        /*!
         * @brief get if the network should try to connect
         * @return true if the network should try to connect
         */
        bool isTryingToConnected() const;
        /*!
         * @brief Try to connect to the server
         * @param username the username to use
         */
        void connect(const std::string &username);
        /*!
         * @brief Get if the user is connected
         * @return true if the user is connected
         */
        bool isConnnected() const;
        /*!
         * @brief Get if the connection failed
         * @return true if a failure occured
         */
        bool failedToConnect() const;
        /*!
         * @brief Get the connection message error
         * @return the error message
         */
        const std::string &getConnectionErrorMessage() const;

        /*!
         * @brief Set the connection status
         * @param isSuccess is the connection successfull
         * @param errorMessage the error message if not successfull
         */
        void setConnectionStatus(bool isSuccess, const std::string &errorMessage = "");

        /*!
         * @brief Indicate that the client lost connection to the server
         * @return true if the client lost connection
         */
        bool hasLostConnection() const;

        /*!
         * @brief Set the lost connection value
         * @param value The value to set to
         */
        void setLostConnection(bool value);
        /*!
         * @brief get the score for the 4 players
         * @return the score
         */
        const std::tuple<int, int, int, int> &getScores() const;
        /*!
         * @brief Set the score for all four players
         * @param scores the new scores to set
         */
        void setScores(const std::tuple<int, int, int, int> &scores);
        /*!
         * @brief is the player in a fame and not in lobby
         * @return true if the player is in game false otherwise
         */
        bool isInGame() const;
        /*!
         * @brief set the player in game or not
         * @param inGame is the player in game
         */
        void setInGame(bool inGame);
        /*!
         * @brief should play gagain
         * @return true if want to play again
         */
        bool isPlayAgain() const;
        /*!
         * @brief set the should play again variable
         * @param playAgain should play again
         */
        void setPlayAgain(bool playAgain);
    private:

        static bool comparePositionZ(rtype::EntitiesState entity1, rtype::EntitiesState entity2);

        bool _lostConnection;
        bool _tryToConnect;
        bool _isConnected;
        std::string _connectionErrorMessage;
        bool _serverInfoChanged;
        std::string _serverHost;
        unsigned short _serverPort;
        uint8_t _charge;
        std::map<NetworkStateKeys, bool> _inputs;
        std::vector<rtype::EntitiesState> _entities;
        rtype::LobbyState _lobbyState;
        std::tuple<int, int, int, int> _scores;
        bool _inGame;
        bool _playAgain;
    };
}

#endif //R_TYPE_NETWORKSTATE_HPP
