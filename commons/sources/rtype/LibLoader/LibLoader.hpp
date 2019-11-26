#ifndef R_TYPE_LIBLOADER_HPP
#define R_TYPE_LIBLOADER_HPP


#include <ecs/IWorld/IWorld.hpp>
#include <ecs/IECS/IECS.hpp>
#include <filesystem>
#include <map>
#include <ecs/DLLoader/DLLoader.hpp>

namespace rtype {
    class LibLoader {
    private:
        template <typename TypeAPI>
        struct LibLoaded {
            ecs::Version version;
            ecs::DLLoader &loader;
            std::shared_ptr<TypeAPI> api;
            bool toDelete = false;
        };
    public:
        LibLoader(std::unique_ptr<ecs::IECS> &ecs, std::shared_ptr<ecs::IWorld> &world, const std::string &libFolder);

        void index();
        void checkUpdates();

    private:
        void computeSet();
        void loadLib(const std::string libPath);
        void unloadLib(const std::string libPath);
        template <typename TypeAPI> void loadLibs(std::map<std::filesystem::path, LibLoaded<TypeAPI>> &libs);
    private:
        std::unique_ptr<ecs::IECS> &_ecs;
        std::shared_ptr<ecs::IWorld> &_world;
        const std::filesystem::path _entitiesPath;
        const std::filesystem::path _systemsPath;

        std::map<std::filesystem::path, LibLoaded<ecs::IEntityAPI>> _entities;
        std::map<std::filesystem::path, LibLoaded<ecs::ISystemAPI>> _systems;

        int _notifyFileDescriptior;
        fd_set _notifySet;
        fd_set _errorSet;
    };
}

#endif //R_TYPE_LIBLOADER_HPP
