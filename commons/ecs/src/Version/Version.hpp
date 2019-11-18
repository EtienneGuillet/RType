#ifndef _I_VERSION_HPP_
#define _I_VERSION_HPP_

#include <iostream>
#include <vector>

namespace ecs {
    class Version {
    public:
        Version(const std::string &type, int lilianVersion, int _titouanVersion, int _julianVersion, int _etienneVersion);
        ~Version();
        std::vector<int> &getVersions();
        bool operator>(Version &compareVersion);
        bool operator<(Version &compareVersion);
    private:
        std::string _type;
        std::vector<int> _versions;
    };
} /* ecs */

#endif /* _I_VERSION_HPP_ */
