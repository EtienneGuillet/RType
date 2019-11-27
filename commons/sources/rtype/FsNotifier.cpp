#include "FsNotifier.hpp"
#include <sys/inotify.h>
#include <exception/B12SoftwareException.hpp>
#include <cstring>
#include <unistd.h>

void rtype::FsNotifier::addCreateListener(std::filesystem::path path, rtype::FsNotifier::Handler handler) {
    int watchCreateFd = inotify_add_watch(_notifierFdCreate, path.string().c_str(), IN_CREATE);

    if (watchCreateFd < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
    _mapCreatedEvents.insert(std::make_pair(watchCreateFd, handler));
}

void rtype::FsNotifier::addDeletedListener(std::filesystem::path path, rtype::FsNotifier::Handler handler) {
    int watchDeleteFd = inotify_add_watch(_notifierFdDelete, path.string().c_str(), IN_DELETE);

    if (watchDeleteFd < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
    _mapDeletedEvents.insert(std::make_pair(watchDeleteFd, handler));
}

rtype::FsNotifier::FsNotifier() {
    _notifierFdCreate = inotify_init();
    _notifierFdDelete = inotify_init();

    if (_notifierFdCreate < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
    if (_notifierFdDelete < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
}

void rtype::FsNotifier::update() {
    checkNotifier(_notifierFdCreate, _mapCreatedEvents, IN_CREATE);
    checkNotifier(_notifierFdDelete, _mapDeletedEvents, IN_DELETE);
}

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

void rtype::FsNotifier::checkNotifier(int fdNotifier, std::map<int, Handler> map, int mask) {
    fd_set readSet, writeSet, errorSet;
    struct timeval timeout = {
            0,
            1
    };

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
                        it->second(event->name);
                }
            }
        }
    }
}
