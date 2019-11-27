#include "FsNotifier.hpp"
#include <exception/B12SoftwareException.hpp>
#include <cstring>
#include <iostream>

void rtype::FsNotifier::addCreateListener(const Handler &createHandler) {
    #if defined(LINUX)
        int watchCreateFd = inotify_add_watch(_notifierFdCreate, _folderPath.string().c_str(), IN_CREATE | IN_CLOSE_WRITE);

        if (watchCreateFd < 0)
            throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
        _mapCreatedEvents.insert(std::make_pair(watchCreateFd, createHandler));
    #elif defined(WINDOWS)
        _mapCreatedEvents.insert(std::make_pair(0, createHandler));
    #endif
}

void rtype::FsNotifier::addDeletedListener(const Handler &deleteHandle) {
    #if defined(LINUX)
        int watchDeleteFd = inotify_add_watch(_notifierFdDelete, _folderPath.string().c_str(), IN_DELETE);

        if (watchDeleteFd < 0)
            throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
        _mapDeletedEvents.insert(std::make_pair(watchDeleteFd, deleteHandle));
    #elif defined(WINDOWS)
        _mapDeletedEvents.insert(std::make_pair(0, deleteHandle));
    #endif
}

void rtype::FsNotifier::update() {
    #if defined(LINUX)
        checkNotifier(_notifierFdCreate, _mapCreatedEvents, IN_CREATE | IN_CLOSE_WRITE);
        checkNotifier(_notifierFdDelete, _mapDeletedEvents, IN_DELETE);
    #elif defined(WINDOWS)
        auto oldPaths = _indexedPaths;

        for (auto &pair : _indexedPaths)
            pair.second = false;
        for (auto &entry : std::filesystem::directory_iterator(_folderPath)) {
            bool toAdd = true;
            for (auto it = _indexedPaths.begin(); it != _indexedPaths.end(); it++) {
                if (it.operator*().first == entry.path()) {
                    it.operator*().second = true;
                    toAdd = false;
                    break;
                }
            }
            if (toAdd) {
                if (_mapCreatedEvents[0](entry.path()) == true)
                    _indexedPaths.insert(std::make_pair(entry.path(), true));;
            }
        }

        for (auto i = _indexedPaths.begin(), last = _indexedPaths.end(); i != last; ) {
            if ((*i).second == false) {
                if (_mapDeletedEvents[0]((*i).first) == true)
                    i = _indexedPaths.erase(i);
            } else {
                ++i;
            }
        }
    #endif
}


#if defined(LINUX)
int rtype::FsNotifier::computeSet(const std::map<int, Handler> &map, fd_set *set, fd_set *errorSet) {
    int maxFd = 0;

    FD_ZERO(set);
    FD_ZERO(errorSet);
    for (const auto &pair : map) {
        FD_SET(pair.first, set);
        FD_SET(pair.first, errorSet);
        maxFd = (std::max)(pair.first, maxFd);
    }
    return maxFd + 1;
}

int rtype::FsNotifier::computeSet(int notifyFd, fd_set *set, fd_set *errorSet) {
    FD_ZERO(set);
    FD_ZERO(errorSet);
    FD_SET(notifyFd, set);
    FD_SET(notifyFd, errorSet);
    return notifyFd + 1;
}
#elif defined(WINDOWS)
#endif

void rtype::FsNotifier::checkNotifier(int fdNotifier, const std::map<int, Handler> &map, int mask) {
    #if defined(LINUX)
        fd_set readSet, writeSet, errorSet;
        struct timeval timeout = {
                0,
                1
        };

        FD_ZERO(&writeSet);
        int selectRes = select(computeSet(fdNotifier, &readSet, &errorSet), &readSet, &writeSet, &errorSet, &timeout);
        if (selectRes < 0)
            throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
        if (FD_ISSET(fdNotifier, &readSet)) {
            constexpr int eventSize = sizeof(struct inotify_event) + 16;
            constexpr size_t buffLen = 1024 * (eventSize);
            char buffer[buffLen] = {0};

            int length = read(fdNotifier, buffer, buffLen);
            struct inotify_event *event = nullptr;

            for (int i = 0; i < length; i += eventSize + event->len) {
                event = (struct inotify_event *) &buffer[i];
                if (event && event->len && !(event->mask & IN_ISDIR)) {
                    if (event->mask & mask) {
                        auto it = std::find_if(map.begin(), map.end(), [event] (const std::pair<int, Handler> &pair) {
                            return event->wd == pair.first;
                        });
                        if (it != map.end())
                            it->second(_folderPath.string() + "/" + std::string(event->name));
                    }
                }
            }
        }
    #elif defined(WINDOWS)
    #endif
}

rtype::FsNotifier::FsNotifier(const std::filesystem::path &folderPath) : _folderPath(folderPath) {
    #if defined(LINUX)
        _notifierFdCreate = inotify_init();
        _notifierFdDelete = inotify_init();

        if (_notifierFdCreate < 0)
            throw b12software::exception::B12SoftwareException(folderPath.string() + std::string(strerror(errno)), WHERE);
        if (_notifierFdDelete < 0)
            throw b12software::exception::B12SoftwareException(folderPath.string() + std::string(strerror(errno)), WHERE);
    #elif defined(WINDOWS)
    #endif
}
