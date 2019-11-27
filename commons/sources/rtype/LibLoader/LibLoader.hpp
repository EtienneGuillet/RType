#ifndef R_TYPE_LIBLOADER_HPP
#define R_TYPE_LIBLOADER_HPP


#include <ecs/IWorld/IWorld.hpp>
#include <ecs/IECS/IECS.hpp>
#include <filesystem>
#include <map>
#include <ecs/DLLoader/DLLoader.hpp>
#include <rtype/FsNotifier/FsNotifier.hpp>

namespace rtype {
    class LibLoader {
    private:
        template <typename TypeAPI>
        struct LibLoaded {
            ecs::Version version;
            std::shared_ptr<TypeAPI> api;
            std::shared_ptr<ecs::DLLoader> loader;
            bool toDelete = false;
        };

        template <typename TypeAPI>
        using MapType = std::map<std::filesystem::path, rtype::LibLoader::LibLoaded<TypeAPI>>;
    public:
        LibLoader(std::unique_ptr<ecs::IECS> &ecs, std::shared_ptr<ecs::IWorld> &world, const std::string &libFolder);
        void checkForChanges();
    private:
        template <typename TypeAPI>
        std::string getEntryPoint();

        template <typename TypeAPI>
        std::string getlibFolder();

        template <typename TypeAPI>
        void loadLib(const std::filesystem::path &libPath, MapType <TypeAPI> &libs);
        template <typename TypeAPI>
        void unloadLib(const std::filesystem::path &libPath, MapType <TypeAPI> &libs);

        void firstLibrariesLoad();
    private:
        std::unique_ptr<ecs::IECS> &_ecs;
        std::shared_ptr<ecs::IWorld> &_world;

        const std::filesystem::path _entitiesPath;
        const std::filesystem::path _systemsPath;

        MapType<ecs::IEntityAPI> _entities;
        MapType<ecs::ISystemAPI> _systems;

        rtype::FsNotifier _notifierEntities;
        rtype::FsNotifier _notifierSystems;
    };
}

#endif //R_TYPE_LIBLOADER_HPP
