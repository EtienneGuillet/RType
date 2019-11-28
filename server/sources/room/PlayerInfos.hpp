/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** PlayerInfos.hpp
*/

/* Created the 27/11/2019 at 14:06 by julian.frabel@epitech.eu */

#ifndef R_TYPE_PLAYERINFOS_HPP
#define R_TYPE_PLAYERINFOS_HPP

#include "EntityInfos.hpp"

namespace rtype {

    class PlayerInfos : public EntityInfos {
    public:
        PlayerInfos();
        ~PlayerInfos();
        PlayerInfos(const PlayerInfos &other);
        PlayerInfos &operator=(const PlayerInfos &rhs);

    public:
        bool isUsed() const;
        void setIsUsed(bool used);
        bool isShooting() const;
        void setIsShooting(bool shooting);
        bool isMovingUp() const;
        void setIsMovingUp(bool movingUp);
        bool isMovingDown() const;
        void setIsMovingDown(bool movingDown);
        bool isMovingLeft() const;
        void setIsMovingLeft(bool movingLeft);
        bool isMovingRight() const;
        void setIsMovingRight(bool movingRight);
        char getCharge() const;
        void setCharge(char charge);
        uint32_t getScore() const;
        void setScore(uint32_t score);

    private:
        std::atomic_bool _used; /*!< Is this player used */
        std::atomic_bool _shooting; /*!< Is this player shooting */
        std::atomic_bool _movingUp; /*!< Is this player moving up */
        std::atomic_bool _movingDown; /*!< Is this player moving down */
        std::atomic_bool _movingLeft; /*!< Is this player moving left */
        std::atomic_bool _movingRight; /*!< Is this player moving right */
        std::atomic_char _charge; /*!< This player shooting charge */
        std::atomic_uint32_t _score;  /*!< This player score */
    };
}
#endif //R_TYPE_PLAYERINFOS_HPP
