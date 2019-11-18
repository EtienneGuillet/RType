#ifndef _DL_LOADER_HPP_
#define _DL_LOADER_HPP_

#include <iostream>

namespace ecs {
    class DLLoader
    {
    public:
        virtual void loadDL(std::string path) = 0;
        virtual void unloadDL(std::string path) = 0;
    };
} /* ecs */

#endif /* _I_COMPONENT_HPP_ */
