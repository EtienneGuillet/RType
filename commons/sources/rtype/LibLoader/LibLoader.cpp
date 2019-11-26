#include <exception/B12SoftwareException.hpp>
#include <logger/DefaultLogger.hpp>
#include "LibLoader.hpp"
#include <sys/inotify.h>
#include <unistd.h>
#include <cstring>

rtype::LibLoader::LibLoader(std::unique_ptr<ecs::IECS> &ecs, std::shared_ptr<ecs::IWorld> &world, const std::string &libFolder) : _ecs(ecs), _world(world), _entitiesPath(libFolder + "/entities"), _systemsPath(libFolder + "/systems"), _notifyFileDescriptior(0) {
    _notifyFileDescriptior = inotify_init();

    if (_notifyFileDescriptior < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
    if (inotify_add_watch(_notifyFileDescriptior, _entitiesPath.string().c_str(), IN_CREATE | IN_DELETE) < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
    if (inotify_add_watch(_notifyFileDescriptior, _systemsPath.string().c_str(), IN_CREATE | IN_DELETE) < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
}

void rtype::LibLoader::index() {
    loadLibs<ecs::IEntityAPI>(_entities);
    loadLibs<ecs::ISystemAPI>(_systems);
}

template<typename TypeAPI>
void rtype::LibLoader::loadLibs(std::map<std::filesystem::path, LibLoaded<TypeAPI>> &libs) {
    std::string entryPoint, libFolder;

    if (std::is_same<TypeAPI, ecs::IEntityAPI>::value) {
        entryPoint = "entryPointEntityAPI";
        libFolder = _entitiesPath;
    } else if(std::is_same<TypeAPI, ecs::ISystemAPI>::value) {
        entryPoint = "entryPointSystemAPI";
        libFolder = _systemsPath;
    } else {
        throw b12software::exception::B12SoftwareException(std::string("Invalid API type used: ") + typeid(TypeAPI).name() , WHERE);
    }

    for (auto &_pair : libs)
        _pair.second.toDelete = true;

    for (const auto &entry : std::filesystem::directory_iterator(libFolder)) {
        if (libs.count(entry.path()) > 0) {
            libs.at(entry.path()).toDelete = false;
        } else {
            try {
                ecs::DLLoader loader(entry.path());
                auto api = loader.loadAPI<TypeAPI>(entryPoint);
                libs.insert(std::make_pair(entry.path(), LibLoaded<TypeAPI> {
                        api->getVersion(),
                        loader,
                        api
                }));
            } catch (const ecs::DLLoaderException &e) {
                std::cerr << "Failed to load " << entry.path() << std::endl;
            }
        }
    }

    auto it = libs.begin();
    while (it != libs.end()) {
        if (it->second.toDelete) {
            auto old = it;
            it++;
            libs.erase(old);
        } else
            it++;
    }
}

void rtype::LibLoader::checkUpdates() {
    fd_set writeSet;
    struct timeval timeout = {
            0,
            1
    };
    computeSet();
    int selectRes = select(_notifyFileDescriptior + 1, &_notifySet, &writeSet, &_errorSet, &timeout);

    if (selectRes < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
    if (selectRes > 0 && FD_ISSET(_notifyFileDescriptior, &_notifySet)) {
        constexpr int eventSize = sizeof(struct inotify_event) + 16;
        constexpr size_t buffLen = 1024 * (eventSize);
        char buffer[buffLen] = {0};

        int length = read(_notifyFileDescriptior, buffer, buffLen);
        struct inotify_event *event = nullptr;

        for (int i = 0; i < length; i += eventSize + event->len) {
            event = (struct inotify_event *) &buffer[i];
            if (event && event->len && !(event->mask & IN_ISDIR)) {
                if (event->mask & IN_DELETE) {
                    unloadLib(event->name);
                } else if (event->mask & IN_CREATE) {
                    loadLib(event->name);
                }
            }
        }
    }
}

void rtype::LibLoader::computeSet() {
    FD_ZERO(&_notifySet);
    FD_ZERO(&_errorSet);
    FD_SET(_notifyFileDescriptior, &_notifySet);
    FD_SET(_notifyFileDescriptior, &_errorSet);
}

void rtype::LibLoader::loadLib(std::string libPath) {
    std::cout << "Loading lib: " << libPath << std::endl;
}

void rtype::LibLoader::unloadLib(const std::string libPath) {
    std::cout << "Unloading lib: " << libPath << std::endl;
}
