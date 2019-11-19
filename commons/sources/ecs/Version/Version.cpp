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

    const std::vector<int> &Version::getVersions() const {
        return _versions;
    }

    bool Version::operator<(const Version &rhs) const {
        std::vector<int> compare = rhs.getVersions();

        if (rhs.getType() != getType())
            return false;
        for (size_t i = 0; i < compare.size() && i < _versions.size(); i++) {
            if (_versions[i] < compare[i])
                return false;
        }
        return true;
    }

    bool Version::operator>(const Version &rhs) const {
        if (rhs.getType() != getType())
            return false;
        return rhs < *this;
    }

    bool Version::operator<=(const Version &rhs) const {
        if (rhs.getType() != getType())
            return false;
        return !(rhs < *this);
    }

    bool Version::operator>=(const Version &rhs) const {
        if (rhs.getType() != getType())
            return false;
        return !(*this < rhs);
    }

    bool Version::operator==(const Version &rhs) const {
        if (rhs.getType() != getType())
            return false;
        return _type == rhs._type &&
               _versions == rhs._versions;
    }

    bool Version::operator!=(const Version &rhs) const {
        if (rhs.getType() != getType())
            return false;
        return !(rhs == *this);
    }

    const std::string &Version::getType() const {
        return _type;
    }
} /* ecs */
