/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** RTypeDatagramScore.hpp
*/

/* Created the 18/11/2019 at 17:39 by julian.frabel@epitech.eu */

#ifndef R_TYPE_RTYPEDATAGRAMSCORE_HPP
#define R_TYPE_RTYPEDATAGRAMSCORE_HPP

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
         * @struct RTypeDatagramScore
         * @brief A structure describing a game score
         */
        struct RTypeDatagramScore {
            unsigned int p1Score; /*!< Player 1 score*/
            unsigned int p2Score; /*!< Player 2 score*/
            unsigned int p3Score; /*!< Player 3 score*/
            unsigned int p4Score; /*!< Player 4 score*/
        };
    }
}

#endif //R_TYPE_RTYPEDATAGRAMSCORE_HPP
