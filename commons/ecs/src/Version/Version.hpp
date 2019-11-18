#ifndef _I_VERSION_HPP_
#define _I_VERSION_HPP_

#include <iostream>

namespace ecs {
    class Version {
    public:
        Version();
        ~Version();
    private:
        std::string &_type;
        int _lilianVersion;
        int _titouanVersion;
        int _julianVersion;
        int _etienneVersion;
    };
} /* ecs */

#endif /* _I_VERSION_HPP_ */
