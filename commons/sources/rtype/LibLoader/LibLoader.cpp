#include <exception/B12SoftwareException.hpp>
#include <logger/DefaultLogger.hpp>
#include "LibLoader.hpp"
#include <cstring>
#include <map>

rtype::LibLoader::LibLoader(std::unique_ptr<ecs::IECS> &ecs, std::shared_ptr<ecs::IWorld> &world, const std::string &libFolder) : _ecs(ecs), _world(world), _entitiesPath(libFolder + "/entities"), _systemsPath(libFolder + "/systems"), _notifierEntities(_entitiesPath), _notifierSystems(_systemsPath) {
    _notifierEntities.addCreateListener([this] (const std::filesystem::path &path) {
        loadLib<ecs::IEntityAPI>(path, _entities);
    });
    _notifierEntities.addDeletedListener([this] (const std::filesystem::path &path) {
        unloadLib<ecs::IEntityAPI>(path, _entities);
    });
    _notifierSystems.addCreateListener([this] (const std::filesystem::path &path) {
        loadLib<ecs::ISystemAPI>(path, _systems);
    });
    _notifierSystems.addDeletedListener([this] (const std::filesystem::path &path) {
        unloadLib<ecs::ISystemAPI>(path, _systems);
    });
    firstLibrariesLoad();
}

template <typename TypeAPI>
void rtype::LibLoader::loadLib(const std::filesystem::path &libPath, MapType <TypeAPI> &libs) {
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::string("[Loading lib] ") + libPath.string());
    try {
        std::shared_ptr<ecs::DLLoader> loader(new ecs::DLLoader(libPath.string()));
        auto api = loader->loadAPI<TypeAPI>(getEntryPoint<TypeAPI>());
        libs.insert(std::make_pair(libPath, LibLoaded<TypeAPI> {
                api->getVersion(),
                api,
                loader
        }));
        if constexpr (std::is_same<TypeAPI, ecs::IEntityAPI>::value) {
          _ecs->learnEntity(api);
        } else if (std::is_same<TypeAPI, ecs::ISystemAPI>::value) {
            auto systemApi = std::dynamic_pointer_cast<ecs::ISystemAPI>(api);
            _ecs->learnSystem(api);
            _world->addSystem(systemApi->createNewSystem());
        } else {
            throw b12software::exception::B12SoftwareException(std::string("Invalid API type used: ") + typeid(TypeAPI).name() , WHERE);
        }
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::string("[Lib loaded] ") + libPath.string());
    } catch (const ecs::DLLoaderException &e) {
        b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelError, std::string("[Failed to load lib] ") + libPath.string());
    }
}

template <typename TypeAPI>
void rtype::LibLoader::unloadLib(const std::filesystem::path &libPath, MapType <TypeAPI> &libs) {
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::string("[Lib unload] ") + libPath.string());
    for (auto i = libs.begin(), last = libs.end(); i != last; ) {
        if ((*i).first == libPath) {
            //TODO Clean systems / entities
            (*i).second.api = std::shared_ptr<TypeAPI>();
            i = libs.erase(i);
        } else {
            ++i;
        }
    }
    b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, std::string("[Lib unloaded] ") + libPath.string());
}

void rtype::LibLoader::firstLibrariesLoad() {
    for (const auto &entry : std::filesystem::directory_iterator(getlibFolder<ecs::ISystemAPI>())) {
        loadLib<ecs::ISystemAPI>(entry.path(), _systems);
    }
    for (const auto &entry : std::filesystem::directory_iterator(getlibFolder<ecs::IEntityAPI>())) {
        loadLib<ecs::IEntityAPI>(entry.path(), _entities);
    }
}

template<typename TypeAPI>
std::string rtype::LibLoader::getEntryPoint() {
    if (std::is_same<TypeAPI, ecs::IEntityAPI>::value)
        return "entryPointEntityAPI";
    else if(std::is_same<TypeAPI, ecs::ISystemAPI>::value)
        return "entryPointSystemAPI";
    else
        throw b12software::exception::B12SoftwareException(std::string("Invalid API type used: ") + typeid(TypeAPI).name() , WHERE);
}

template<typename TypeAPI>
std::string rtype::LibLoader::getlibFolder() {
    if (std::is_same<TypeAPI, ecs::IEntityAPI>::value)
        return _entitiesPath.string();
    else if(std::is_same<TypeAPI, ecs::ISystemAPI>::value)
        return _systemsPath.string();
    else
        throw b12software::exception::B12SoftwareException(std::string("Invalid API type used: ") + typeid(TypeAPI).name() , WHERE);
}

void rtype::LibLoader::checkForChanges() {
    try {
        _notifierSystems.update();
        _notifierEntities.update();
    } catch (const b12software::exception::B12SoftwareException &e) {}
}