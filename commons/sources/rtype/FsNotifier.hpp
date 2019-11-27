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
        FsNotifier();
        void update();
        void addCreateListener(std::filesystem::path path, Handler handler);
        void addDeletedListener(std::filesystem::path path, Handler handler);

    private:
        int computeSet(const std::map<int, Handler> &map, fd_set *set, fd_set *errorSet);
        int computeSet(int notifyFd, fd_set *set, fd_set *errorSet);
    private:
        int _notifierFdCreate;
        int _notifierFdDelete;

        std::map<int, Handler> _mapCreatedEvents;
        std::map<int, Handler> _mapDeletedEvents;
    };
}

#endif //R_TYPE_FSNOTIFIER_HPP
