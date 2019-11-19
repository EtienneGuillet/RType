#include "Version.hpp"

namespace ecs {
    Version::Version(const std::string &type, int lilianVersion, int titouanVersion, int julianVersion, int etienneVersion)
        : _type(type), _versions()
    {
        _versions.push_back(lilianVersion);
        _versions.push_back(titouanVersion);
        _versions.push_back(julianVersion);
        _versions.push_back(etienneVersion);
    }

    Version::~Version() {
    }

    std::vector<int> &Version::getVersions() {
        return _versions;
    }

    bool Version::operator>(Version &compareVersion) {
        std::vector<int> compare = compareVersion.getVersions();

        for (size_t i = 0; i < compare.size() && i < _versions.size(); i++) {
            if (_versions[i] < compare[i])
                return false;
        }
        return true;
    }

    bool Version::operator<(Version &compareVersion) {
        std::vector<int> compare = compareVersion.getVersions();

        for (size_t i = 0; i < compare.size() && i < _versions.size(); i++) {
            if (_versions[i] < compare[i])
                return true;
        }
        return false;
    }
} /* ecs */
