#ifndef R_TYPE_LIBLOADER_HPP
#define R_TYPE_LIBLOADER_HPP


#include <ecs/IWorld/IWorld.hpp>
#include <ecs/IECS/IECS.hpp>
#include <filesystem>
#include <map>
#include "where.hpp"
#include <ecs/DLLoader/DLLoader.hpp>
#include <rtype/FsNotifier/FsNotifier.hpp>
/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {
    /*!
     * @class LibLoader
     * @brief A class to load and unload libraries on file creation / deletion
     */
    class LibLoader {
    private:
        /*!
         * @struct A structure containing all informations related to ecs::DLLoader
         * @tparam TypeAPI The type of the API contained in API field (should be ecs::IEntityAPI or ecs::ISystemAPI)
         */
        template <typename TypeAPI>
        struct LibLoaded {
            /*!
             * @brief dtor
             */
            ~LibLoaded() {
                api = std::shared_ptr<TypeAPI>();
            }

            ecs::Version version; /*!< The version of the thing loaded */
            std::shared_ptr<TypeAPI> api; /*!< The api extracted from lib */
            std::shared_ptr<ecs::DLLoader> loader; /*!< The DLLoader used to load library */
        };

        /*!
         * @tparam TypeAPI
         * @brief The map type to associate a path and a LibLoaded<TypeAPI>
         */
        template <typename TypeAPI>
        using MapType = std::map<std::filesystem::path, rtype::LibLoader::LibLoaded<TypeAPI>>;
    public:
        /*!
         * @brief ctor
         * @param ecs The ecs which should learn loaded systems
         * @param world The world into which we want to add systems
         * @param libFolder The folder containing server and entities folder which contains shared libraries
         */
        LibLoader(std::unique_ptr<ecs::IECS> &ecs, std::shared_ptr<ecs::IWorld> &world, const std::string &libFolder);

        /*!
         * @brief The method to use to check for new libraries to load or libraries removed to delete
         */
        void checkForChanges();
    private:
        /*!
         * @brief Get the entry point for a type of library
         * @tparam TypeAPI The type of API
         * @returns A string containing the entryPoint for the requested lib type
         */
        template <typename TypeAPI>
        std::string getEntryPoint();

        /*!
         * @brief Get the folder containing a type of library
         * @tparam TypeAPI The type of API
         * @returns A string containing the name of the folder for the requested lib type
         */
        template <typename TypeAPI>
        std::string getlibFolder();

        /*!
         * @brief Load a library
         * @tparam TypeAPI The type of API
         * @param libPath The path of the library to load
         * @param libs The map into which insert the lib once loaded
         */
        template <typename TypeAPI>
        void loadLib(const std::filesystem::path &libPath, MapType <TypeAPI> &libs);

        /*!
         * @brief Unload a library
         * @tparam TypeAPI The type of API
         * @param libPath The path of the library to unload
         * @param libs The map for which remove the lib
         */
        template <typename TypeAPI>
        void unloadLib(const std::filesystem::path &libPath, MapType <TypeAPI> &libs);

        /*!
         * @brief The first load before using notifiers
         */
        void firstLibrariesLoad();
    private:
        std::unique_ptr<ecs::IECS> &_ecs; /*< The ecs which should learn loaded systems */
        std::shared_ptr<ecs::IWorld> &_world; /*< The world into which we want to add systems */

        const std::filesystem::path _entitiesPath; /*< The path of the folder containing the entities libraries */
        const std::filesystem::path _systemsPath; /*< The path of the folder containing the systems libraries */

        MapType<ecs::IEntityAPI> _entities; /*< A map of loaded entities */
        MapType<ecs::ISystemAPI> _systems; /*< A map of loaded systems */

        rtype::FsNotifier _notifierEntities; /*< A notifier for entities */
        rtype::FsNotifier _notifierSystems; /*< A notifier for systems */
    };
}

#endif //R_TYPE_LIBLOADER_HPP
