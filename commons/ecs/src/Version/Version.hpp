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
        Version(const std::string &type, int lilianVersion, int _titouanVersion, int _julianVersion, int _etienneVersion);

        /*!
         * @brief Dtor.
         */
        ~Version();

        /*!
         * @brief Return a vector of the versions of every contributor, 4 in our instance.
         */
        std::vector<int> &getVersions();

        /*!
         * @brief Return a boolean, whether the version asked as parameter is inferior or not.
         */
        bool operator>(Version &compareVersion);

        /*!
         * @brief Return a boolean, whether the version asked as parameter is superior or not.
         */
        bool operator<(Version &compareVersion);

    private:
        std::string _type;
        std::vector<int> _versions;
    };
} /* ecs */

#endif /* _I_VERSION_HPP_ */
