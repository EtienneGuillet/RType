#ifndef R_TYPE_FSNOTIFIER_HPP
#define R_TYPE_FSNOTIFIER_HPP

#include <map>
#include <filesystem>
#include <functional>

#if defined(__linux__)
    #ifndef LINUX
        #define LINUX
        #include <sys/inotify.h>
        #include <unistd.h>
    #endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #include <Windows.h>
    #ifndef WINDOWS
        #define WINDOWS
    #endif
#else
    #error "This os distribution is not supported"
#endif

namespace rtype {
    class FsNotifier {
    public:
        typedef std::function<bool (std::filesystem::path)> Handler;

    public:
        explicit FsNotifier(const std::filesystem::path &folderPath);
        void update();
        void addCreateListener(const Handler &createHandler);

        void addDeletedListener(const Handler &deleteHandle);

    private:
        #if defined(LINUX)
            int computeSet(const std::map<int, Handler> &map, fd_set *set, fd_set *errorSet);
            int computeSet(int notifyFd, fd_set *set, fd_set *errorSet);
        #elif defined(WINDOWS)
        #endif


        void checkNotifier(int fdNotifier, const std::map<int, Handler> &map, int mask);

    private:
        std::filesystem::path _folderPath;

        int _notifierFdCreate;
        int _notifierFdDelete;

        std::map<int, Handler> _mapCreatedEvents;
        std::map<int, Handler> _mapDeletedEvents;

        #if defined(WINDOWS)
            std::map<std::filesystem::path, bool> _indexedPaths;
        #endif
    };
}

#endif //R_TYPE_FSNOTIFIER_HPP
