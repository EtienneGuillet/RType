#ifndef _I_VERSION_HPP_
#define _I_VERSION_HPP_

#include <iostream>
#include <vector>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class Version
     * @brief This class describe the version of a component.
     */
    class Version {
    public:

        /*!
         * @brief Ctor.
         */
        Version(const std::string &type, int lilianVersion, int titouanVersion, int julianVersion, int etienneVersion);

        /*!
         * @brief Dtor.
         */
        ~Version() = default;

        /*!
         * @brief Return a vector of the versions of every contributor, 4 in our instance.
         * @return A vector which contains every version number
         */
        const std::vector<int> &getVersions() const;

        /*!
         * @brief Return a string of the type
         * @return the version type
         */
        const std::string &getType() const;

        /*!
         * @brief operator <
         * @param rhs right hand side
         * @return true or false
         */
        bool operator<(const Version &rhs) const;

        /*!
         * @brief operator >
         * @param rhs right hand side
         * @return true or false
         */
        bool operator>(const Version &rhs) const;

        /*!
         * @brief operator <=
         * @param rhs right hand side
         * @return true or false
         */
        bool operator<=(const Version &rhs) const;

        /*!
         * @brief operator >=
         * @param rhs right hand side
         * @return true or false
         */
        bool operator>=(const Version &rhs) const;

        /*!
         * @brief operator ==
         * @param rhs right hand side
         * @return true or false
         */
        bool operator==(const Version &rhs) const;

        /*!
         * @brief operator ==
         * @param rhs right hand side
         * @return true or false
         */
        bool operator!=(const Version &rhs) const;
    private:
        std::string _type;
        std::vector<int> _versions;
    };
} /* ecs */

#endif /* _I_VERSION_HPP_ */
