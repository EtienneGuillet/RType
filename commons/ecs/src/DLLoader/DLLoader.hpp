#ifndef _DL_LOADER_HPP_
#define _DL_LOADER_HPP_

#include <iostream>

namespace ECS {
    class DLLoader
    {
    public:
        virtual void loadDL(std::string path) = 0;
        virtual void unloadDL(std::string path) = 0;
    };
} /* ECS */

#endif /* _I_COMPONENT_HPP_ */
