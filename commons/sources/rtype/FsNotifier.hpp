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

    private:
        int _notifierFdCreate;
        int _notifierFdDelete;

    };
}

#endif //R_TYPE_FSNOTIFIER_HPP
