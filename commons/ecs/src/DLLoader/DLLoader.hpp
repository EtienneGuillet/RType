#ifndef _DL_LOADER_HPP_
#define _DL_LOADER_HPP_

#include <iostream>

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class DLLoader
     * @brief A class that is used to load dynamic library, using path name.
     */
    class DLLoader
    {
    public:

        /*!
         * @brief Load a dynamic library.
         */
        virtual void loadDL(std::string path) = 0;

        /*!
         * @brief Unload a dynamic library.
         */
        virtual void unloadDL(std::string path) = 0;
    };
} /* ecs */

#endif /* _I_COMPONENT_HPP_ */
