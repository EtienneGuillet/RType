#ifndef _DL_LOADER_HPP_
#define _DL_LOADER_HPP_

#include <iostream>
#include <memory>
#include <fstream>
#include "DLLoaderException.hpp"
#include "exception/B12SoftwareException.hpp"

#if defined(__linux__)
    #include <dlfcn.h>
    #ifndef LINUX
        #define LINUX
    #endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
	#define _WINSOCKAPI_
	#include <Windows.h>
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
         * @throw DLLoader exception if the library wasn't found
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
         * @brief copy ctor deleted
         */
        DLLoader(DLLoader &) = delete;
        /*!
         * @brief copy ctor deleted
         */
        DLLoader &operator =(DLLoader &) = delete;

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

        /*!
         * @brief Return an API from entry point
         * @tparam API Type of API
         * @param entryPoint Entrypoint name
         * @return A shared ptr of the API
         * @throw DLLoader exception if the entrypoint wasn't found
         */
        template<typename API>
        std::shared_ptr<API> loadAPI(const std::string &entryPoint) const
        {
#if defined(LINUX)
            using EntryFunc = API *(*)();
            EntryFunc entry = reinterpret_cast<EntryFunc>(dlsym(_instance, entryPoint.c_str()));
            if (entry == nullptr) {
                throw DLLoaderException(dlerror(), WHERE);
            }
            return std::shared_ptr<API>((*entry)());
#else
            using EntryFunc = API *(*)();
            EntryFunc entry = reinterpret_cast<EntryFunc>(GetProcAddress(_instance, entryPoint.c_str()));
            if (entry == NULL) {
                throw DLLoaderException("Failed to find function '" + entryPoint + "'", WHERE);
            }
            return std::shared_ptr<API>((entry)());
#endif
        }

    private:
        HandlerType _instance;
    };
} /* ecs */

#endif /* _I_COMPONENT_HPP_ */