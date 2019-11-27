#ifndef R_TYPE_FSNOTIFIER_HPP
#define R_TYPE_FSNOTIFIER_HPP

#include <map>
#include <filesystem>
#include <functional>

namespace rtype {
    class FsNotifier {
    public:
        typedef std::function<void (std::filesystem::path)> Handler;
    private:
        typedef struct {
            int fdWatch;
            int mask;
            Handler handler;
        } WatchedItem;

    public:
        explicit FsNotifier(const std::filesystem::path &folderPath);
        void update();
        void addCreateListener(const Handler &createHandler);
        void addDeletedListener(const Handler &deleteHandle);

    private:
        int computeSet(const std::map<int, Handler> &map, fd_set *set, fd_set *errorSet);
        int computeSet(int notifyFd, fd_set *set, fd_set *errorSet);

        void checkNotifier(int fdNotifier, const std::map<int, Handler> &map, int mask);

    private:
        std::filesystem::path _folderPath;

        int _notifierFdCreate;
        int _notifierFdDelete;

        std::map<int, Handler> _mapCreatedEvents;
        std::map<int, Handler> _mapDeletedEvents;
    };
}

#endif //R_TYPE_FSNOTIFIER_HPP
