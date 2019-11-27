#include "FsNotifier.hpp"
#include <sys/inotify.h>
#include <exception/B12SoftwareException.hpp>
#include <cstring>

void rtype::FsNotifier::addCreateListener(std::filesystem::path path, rtype::FsNotifier::Handler handler) {
    int watchCreateFd = inotify_add_watch(_notifierFdCreate, path.string().c_str(), IN_CREATE | IN_DELETE);
}

void rtype::FsNotifier::addDeletedListener(std::filesystem::path path, rtype::FsNotifier::Handler handler) {

}

rtype::FsNotifier::FsNotifier() {
    _notifierFdCreate = inotify_init();
    _notifierFdDelete = inotify_init();

    if (_notifierFdCreate < 0 || _notifierFdDelete < 0)
        throw b12software::exception::B12SoftwareException(strerror(errno), WHERE);
}

void rtype::FsNotifier::update() {

}


/*void rtype::LibLoader::checkUpdates() {
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
                    std::cout << event->wd
                    //loadLib(event->name);
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
}*/
