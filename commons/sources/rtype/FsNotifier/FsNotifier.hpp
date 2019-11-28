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

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {
    /*!
     * @class FsNotifier
     * @brief A class is used to watch a directory and calls a CB function when a file is created or deleted inside it
     */
    class FsNotifier {
    public:
        /*!
         * @typedef The handler type used for callbacks
         */
        typedef std::function<bool (std::filesystem::path)> Handler;

    public:
        /*!
         * @brief ctor
         * @param folderPath The path of the directory to watch
         * @throws b12software::exception::B12SoftwareException If the folder isn't found
         */
        explicit FsNotifier(const std::filesystem::path &folderPath);

        /*!
         * @brief The method that has to be called when you want to check for changes
         */
        void update();

        /*!
         * @brief Adds a listener for creation
         * @param createHandler The handle that will be called upon creation
         * @throws b12software::exception::B12SoftwareException
         */
        void addCreateListener(const Handler &createHandler);

        /*!
         * @brief Adds a listener for deletion
         * @param createHandler The handle that will be called upon deletion
         * @throws b12software::exception::B12SoftwareException
         */
         void addDeletedListener(const Handler &deleteHandle);

    private:
        #if defined(LINUX)
            /*!
             * @brief Compute readSet and errorSet from fd list
             * @param map The map containing the fds to compute
             * @param set The readSet
             * @param errorSet The errorSet
             * @return The max fd of the set
             */
            int computeSet(const std::map<int, Handler> &map, fd_set *set, fd_set *errorSet);

            /*!
             * @brief Compute readSet and errorSet from a specific fd
             * @param notifyFd The fd to put un set and errorSet
             * @param set The readSet
             * @param errorSet The errorSet
             * @return The max fd of the set
             */
            int computeSet(int notifyFd, fd_set *set, fd_set *errorSet);
        #endif

        /*!
         * @brief Checks for changes of a notifier fd
         * @param map The map containing the fds to compute
         * @param mask The readSet
         */
        void checkNotifier(int fdNotifier, const std::map<int, Handler> &map, int mask);

    private:
        std::filesystem::path _folderPath; /*!< The path of the directory to watch */

        int _notifierFdCreate; /*!< The notifier file descriptor for creations */
        int _notifierFdDelete; /*!< The notifier file descriptor for deletions */

        std::map<int, Handler> _mapCreatedEvents; /*!< The map of watch fd  and handlers associated for creations */
        std::map<int, Handler> _mapDeletedEvents; /*!< The map of watch fd  and handlers associated for deletions */

        #if defined(WINDOWS)
            std::map<std::filesystem::path, bool> _indexedPaths; /*!< The map of path indexed and a boolean to know if they are to be removed */
        #endif
    };
}

#endif //R_TYPE_FSNOTIFIER_HPP
