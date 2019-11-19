#ifndef _DL_LOADER_HPP_
#define _DL_LOADER_HPP_

#include <iostream>
#include <memory>
#include "DLLoaderException.hpp"

#if defined(__linux__)
    #include <dlfcn.h>
    #ifndef LINUX
        #define LINUX
    #endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #include <windows.h>
    #ifndef WINDOWS
        #define WINDOWS
    #endif
#else
    #error "This os distribution is not supported"
#endif

/*!
 * @namespace ecs
 * @brief Main namespace for all ecs related classes.
 */
namespace ecs {

    /*!
     * @class DLLoader
     * @brief A class that is used to load dynamic library, using path name.
     */
    class DLLoader {
    private:
#if defined(LINUX)
        using HandlerType = void *;
#else
        using HandlerType = HINSTANCE;
#endif

    public:
        /*!
         * @brief ctor
         * @param libraryPath the path of the library to load
         */
        explicit DLLoader(const std::string &libraryPath)
            : _instance()
        {
#if defined(LINUX)
            _instance = dlopen(libraryPath.c_str(), RTLD_LAZY);
            if (_instance == nullptr) {
                throw DLLoaderException(dlerror(), WHERE);
            }
#else
            _instance = LoadLibrary(TEXT(libraryPath.c_str()));
            if (_instance == NULL) {
                throw DLLoaderException("Failed to load '" + libraryPath + "'", WHERE);
            }
#endif
        }

        /*!
         * @brief dtor
         */
        ~DLLoader()
        {
#if defined(LINUX)
            dlclose(_instance);
#else
            FreeLibrary(_instance);
#endif
        }

        template<typename API>
        std::shared_ptr<API> loadAPI(const std::string &entryPoint) const
        {
#if defined(LINUX)
            using EntryFunc = std::shared_ptr<API> (*)();
            EntryFunc entry = reinterpret_cast<EntryFunc>(dlsym(_instance, entryPoint.c_str()));
            if (entry == nullptr) {
                throw DLLoaderException(dlerror(), WHERE);
            }
            return (*entry)();
#else
            using EntryFunc = std::shared_ptr<API> (__cdecl *)();
            EntryFunc entry = reinterpret_cast<EntryFunc>(GetProcAddress(_instance, entryPoint.c_str()));
            if (entry == NULL) {
                throw DLLoaderException("Failed to find function '" + entryPoint + "'", WHERE);
            }
            return (entry)();
#endif
        }

    private:
        HandlerType _instance;
    };
} /* ecs */

#endif /* _I_COMPONENT_HPP_ */
