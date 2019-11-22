/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ThreadSafeList.hpp
*/

/* Created the 22/11/2019 at 17:45 by julian.frabel@epitech.eu */

#ifndef R_TYPE_THREADSAFELIST_HPP
#define R_TYPE_THREADSAFELIST_HPP

#include <mutex>
#include <condition_variable>
#include <list>

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
         * @class ThreadSafeList
         * @brief A thread safe list
         * @tparam T the type of elements in the list
         */
        template<typename T>
        class ThreadSafeList {
        public:
            /*!
             * @brief ctor
             */
            ThreadSafeList();
            /*!
             * @brief cpy ctor
             * @param other the other thread safe list to create from
             */
            ThreadSafeList(const ThreadSafeList<T> &other);

            /*!
             * @brief Assignment operator
             * @param rhs The thread safe list to assign to
             * @return *this
             */
            ThreadSafeList<T> &operator=(const ThreadSafeList<T> &rhs);

            /*!
             * @brief Return the front element see std::list@front for more information
             * @return The front element
             */
            T &front();
            /*!
             * @brief Return the back element see std::list@back for more information
             * @return The back element
             */
            T &back();

            /*!
             * @brief Check if a list is empty (see std::list@empty for more information)
             * @return true of the list is empty false otherwise
             */
            bool empty() const;
            /*!
             * @brief Return the size of the list (see std::list@size for more information)
             * @return The size of the list
             */
            size_t size() const;

            /*!
             * @brief Get an iterator on the list
             * @return an iterator on the start of the list
             */
            typename std::list<T>::iterator begin();
            /*!
             * @brief Get a const iterator on the list
             * @return an iterator on the start of the list
             */
            typename std::list<T>::const_iterator begin() const;

            /*!
             * @brief Get an iterator on the list
             * @return an iterator on the end of the list
             */
            typename std::list<T>::iterator end();
            /*!
             * @brief Get a const iterator on the list
             * @return an iterator on the end of the list
             */
            typename std::list<T>::const_iterator end() const;

            /*!
             * @brief erase all the elements in the list
             */
            void clear();
            /*!
             * @brief Push an lvalue to the list (see std::list@push_back for more information)
             * @param elem the lvalue to add to the list
             */
            void push_back(const T &elem);
            /*!
             * @brief Push an rvalue to the list (see std::list@push_back for more information)
             * @param elem the rvalue to add to the list
             */
            void push_back(T &&elem);
            /*!
             * @brief remove the element from the list (see std::list@remove for more information)
             * @param value element value to remove
             */
            void remove(const T &value);
            /*!
             * @brief remove the element from the list (see std::list@remove for more information)
             * @tparam UnaryPredicate the type of predicate
             * @param p the predicate
             */
            template<class UnaryPredicate>
            void remove_if(UnaryPredicate p);

            /*!
             * @brief Manually lock the list
             * This can be usefull to compute large operations on a list without wanting other threads to interfere
             * WARNING: don't forget to unlock the list or you will be facing deadlocks
             */
            void lock();

            /*!
             * @brief Manually unlock a locked list
             */
            void unlock();

            /*!
             * @brief Manually trylock a list
             */
            void trylock();

        private:
            mutable std::recursive_mutex _mutex; /*!< The internal mutex */
            std::list<T> _list; /*!< The internal list */
        };

        template<typename T>
        ThreadSafeList<T>::ThreadSafeList(): _mutex(), _list()
        {

        }

        template<typename T>
        ThreadSafeList<T>::ThreadSafeList(const ThreadSafeList<T> &other): _mutex(), _list(other._list)
        {

        }

        template<typename T>
        ThreadSafeList<T> &ThreadSafeList<T>::operator=(const ThreadSafeList<T> &rhs)
        {
            if (&rhs == this)
                return *this;
            std::scoped_lock lock(rhs._mutex, _mutex);
            _list = rhs._list;
            return *this;
        }

        template<typename T>
        T &ThreadSafeList<T>::front()
        {
            std::scoped_lock lock(_mutex);
            return _list.front();
        }

        template<typename T>
        T &ThreadSafeList<T>::back()
        {
            std::scoped_lock lock(_mutex);
            return _list.back();
        }

        template<typename T>
        bool ThreadSafeList<T>::empty() const
        {
            std::scoped_lock lock(_mutex);
            return _list.empty();
        }

        template<typename T>
        size_t ThreadSafeList<T>::size() const
        {
            std::scoped_lock lock(_mutex);
            return _list.size();
        }

        template<typename T>
        typename std::list<T>::iterator ThreadSafeList<T>::begin()
        {
            return _list.begin();
        }

        template<typename T>
        typename std::list<T>::const_iterator ThreadSafeList<T>::begin() const
        {
            return _list.begin();
        }

        template<typename T>
        typename std::list<T>::iterator ThreadSafeList<T>::end()
        {
            return _list.end();
        }

        template<typename T>
        typename std::list<T>::const_iterator ThreadSafeList<T>::end() const
        {
            return _list.end();
        }

        template<typename T>
        void ThreadSafeList<T>::clear()
        {
            std::scoped_lock lock(_mutex);
            return _list.clear();
        }

        template<typename T>
        void ThreadSafeList<T>::push_back(const T &elem)
        {
            std::scoped_lock lock(_mutex);
            return _list.push_back(elem);
        }

        template<typename T>
        void ThreadSafeList<T>::push_back(T &&elem)
        {
            std::scoped_lock lock(_mutex);
            return _list.push_back(elem);
        }

        template<typename T>
        void ThreadSafeList<T>::remove(const T &value)
        {
            std::scoped_lock lock(_mutex);
            return _list.remove(value);
        }

        template<typename T>
        template<class UnaryPredicate>
        void ThreadSafeList<T>::remove_if(UnaryPredicate p)
        {
            std::scoped_lock lock(_mutex);
            return _list.remove_if(p);
        }

        template<typename T>
        void ThreadSafeList<T>::lock()
        {
            _mutex.lock();
        }

        template<typename T>
        void ThreadSafeList<T>::unlock()
        {
            _mutex.unlock();
        }

        template<typename T>
        void ThreadSafeList<T>::trylock()
        {
            _mutex.try_lock();
        }
    }
}

#endif //R_TYPE_THREADSAFELIST_HPP
