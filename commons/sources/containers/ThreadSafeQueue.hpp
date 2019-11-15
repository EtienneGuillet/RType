/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** ThreadSafeQueue.hpp
*/

/* Created the 28/10/2019 at 16:37 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_THREADSAFEQUEUE_HPP
#define B12NETWORKING_THREADSAFEQUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <queue>

/*!
 * @namespace b12software
 * @brief Main namespace for all b12 software
 */
namespace b12software {

    /*!
     * @namespace b12software::containers
     * @brief Main namespace for custom containers
     */
    namespace containers {

        /*!
         * @class ThreadSafeQueue
         * @brief A thread safe queue
         * @tparam T the type of elements in the queue
         */
        template<typename T>
        class ThreadSafeQueue {
        public:
            /*!
             * @brief ctor
             */
            ThreadSafeQueue();
            /*!
             * @brief cpy ctor
             * @param other the other thread safe queue to create from
             */
            ThreadSafeQueue(const ThreadSafeQueue<T> &other);

            /*!
             * @brief Assignment operator
             * @param rhs The thread safe queue to assign to
             * @return *this
             */
            ThreadSafeQueue<T> &operator=(const ThreadSafeQueue<T> &rhs);

            /*!
             * @brief Return the front element see std::queue@front for more information
             * @return The front element
             */
            T &front();
            /*!
             * @brief Return the back element see std::queue@back for more information
             * @return The back element
             */
            T &back();

            /*!
             * @brief Check if a queue is empty (see std::queue@empty for more information)
             * @return true of the queue is empty false otherwise
             */
            bool empty() const;
            /*!
             * @brief Return the size of the queue (see std::queue@size for more information)
             * @return The size of the queue
             */
            size_t size() const;

            /*!
             * @brief Push an lvalue to the queue (see std::queue@push for more information)
             * @param elem the lvalue to add to the queue
             */
            void push(const T &elem);
            /*!
             * @brief Push an rvalue to the queue (see std::queue@push for more information)
             * @param elem the rvalue to add to the queue
             */
            void push(T &&elem);
            /*!
             * @brief Emplace an element at the end of the queue (see std::queue@emplace for more information)
             * @tparam Args Types of the arguments
             * @param args the arguments to pass to the constructor of T
             */
            template<class... Args>
            void emplace(Args&&... args);
            /*!
             * @brief pop the front element from the queue (see std::queue@pop for more information)
             */
            void pop();

            /*!
             * @brief Manually lock the queue
             * This can be usefull to compute large operations on a queue without wanting other threads to interfere
             * WARNING: don't forget to unlock the queue or you will be facing deadlocks
             */
            void lock();

            /*!
             * @brief Manually unlock a locked queue
             */
            void unlock();

            /*!
             * @brief Manually trylock a queue
             */
            void trylock();

        private:
            mutable std::recursive_mutex _mutex; /*!< The internal mutex */
            std::condition_variable_any _variable; /*!< Conditional variable that notify when data becomes available*/
            std::queue<T> _queue; /*!< The internal queue */
        };

        template<typename T>
        ThreadSafeQueue<T>::ThreadSafeQueue()
            : _mutex(), _variable(), _queue()
        {

        }

        template<typename T>
        ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> &other)
            : _mutex(), _variable(), _queue()
        {
            std::scoped_lock lock(_mutex, other._mutex);
            _queue = other._queue;
        }

        template<typename T>
        ThreadSafeQueue<T> &ThreadSafeQueue<T>::operator=(const ThreadSafeQueue<T> &rhs)
        {
            if (&rhs == this)
                return *this;
            int size = 0;
            {
                std::scoped_lock lock(_mutex, rhs._mutex);
                _queue = rhs._queue;
                size = _queue.size();
            }
            if (size == 1)
                _variable.notify_one();
            else if (size > 1)
                _variable.notify_all();
            return *this;
        }

        template<typename T>
        T &ThreadSafeQueue<T>::front()
        {
            std::unique_lock lock(_mutex);
            while (_queue.empty()) {
                _variable.wait(lock);
            }
            return _queue.front();
        }

        template<typename T>
        T &ThreadSafeQueue<T>::back()
        {
            std::unique_lock lock(_mutex);
            while (_queue.empty()) {
                _variable.wait(lock);
            }
            return _queue.back();
        }

        template<typename T>
        bool ThreadSafeQueue<T>::empty() const
        {
            std::scoped_lock lock(_mutex);
            return _queue.empty();
        }

        template<typename T>
        size_t ThreadSafeQueue<T>::size() const
        {
            std::scoped_lock lock(_mutex);
            return _queue.size();
        }

        template<typename T>
        void ThreadSafeQueue<T>::push(const T &elem)
        {
            std::unique_lock lock(_mutex);
            _queue.push(elem);
            lock.unlock();
            _variable.notify_one();
        }

        template<typename T>
        void ThreadSafeQueue<T>::push(T &&elem)
        {
            std::unique_lock lock(_mutex);
            _queue.push(elem);
            lock.unlock();
            _variable.notify_one();
        }

        template<typename T>
        template<class... Args>
        void ThreadSafeQueue<T>::emplace(Args &&... args)
        {
            std::unique_lock lock(_mutex);
            _queue.emplace(args...);
            lock.unlock();
            _variable.notify_one();
        }

        template<typename T>
        void ThreadSafeQueue<T>::pop()
        {
            std::unique_lock lock(_mutex);
            while (_queue.empty()) {
                _variable.wait(lock);
            }
            _queue.pop();
        }

        template<typename T>
        void ThreadSafeQueue<T>::lock()
        {
            _mutex.lock();
        }

        template<typename T>
        void ThreadSafeQueue<T>::unlock()
        {
            _mutex.unlock();
        }

        template<typename T>
        void ThreadSafeQueue<T>::trylock()
        {
            _mutex.try_lock();
        }
    }
}

#endif //B12NETWORKING_THREADSAFEQUEUE_HPP
