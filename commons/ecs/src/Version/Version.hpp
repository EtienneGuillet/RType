#ifndef _I_VERSION_HPP_
#define _I_VERSION_HPP_

namespace ECS {
    class Version {
    public:
        Version();
    private:
        std::string &_type;
        int _lilianVersion;
        int _titouanVersion;
        int _julianVersion;
        int _etienneVersion;
    };
} /* ECS */

#endif /* _I_VERSION_HPP_ */
