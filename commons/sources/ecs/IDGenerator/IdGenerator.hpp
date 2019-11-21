/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** IdGenerator.hpp
*/

/* Created the 19/11/2019 at 21:02 by julian.frabel@epitech.eu */

#ifndef R_TYPE_IDGENERATOR_HPP
#define R_TYPE_IDGENERATOR_HPP

#include <queue>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class IDGenerator
     * @brief A class that generate unique ids by generator
     */
    class IDGenerator {
    public:
        /*!
         * @brief ctor
         */
        IDGenerator();
        /*!
         * @brief cpy ctor
         * @param other the other id generator to build from
         */
        IDGenerator(const IDGenerator &other);
        /*!
         * @brief dtor
         */
        ~IDGenerator() = default;
        /*!
         * @brief Assignment operator
         * @param rhs the id generator to assign to
         * @return *this
         */
        IDGenerator &operator=(const IDGenerator &rhs);

        /*!
         * @brief generate a new unused id
         * @return the id to use
         */
        int generateNewID();

        /*!
         * @brief Indicate to the generator that this id is not used anymore
         * @param id the id to free
         */
        void freeId(int id);

    private:
        int _maxID; /*!< The maximal id */
        std::queue<int> _freeIds; /*!< The free ids that can be reused */
    };
}

#endif //R_TYPE_IDGENERATOR_HPP
