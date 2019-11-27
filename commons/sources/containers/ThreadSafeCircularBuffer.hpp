/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** ThreadSafeCircularBuffer.hpp
*/

/* Created the 28/10/2019 at 13:36 by julian.frabel@epitech.eu */

#ifndef B12NETWORKING_THREADSAFECIRCULARBUFFER_HPP
#define B12NETWORKING_THREADSAFECIRCULARBUFFER_HPP

#include <mutex>
#include "CircularBuffer.hpp"

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
         * @class ThreadSafeCircularBuffer
         * @brief A thread safe version of b12software::containers::CircularBuffer
         */
    class ThreadSafeCircularBuffer : public CircularBuffer {
        public:
            /*!
             * @brief ctor
             * @param size The size of this circular buffer in bytes
             */
            explicit ThreadSafeCircularBuffer(int size);

        private:
            /*!
             * @brief cpy ctor thread safe
             * @param other The buffer to copy
             */
            ThreadSafeCircularBuffer(const ThreadSafeCircularBuffer &other, const std::lock_guard<std::recursive_mutex> &);

        public:
            /*!
             * @brief cpy ctor
             * @param other The buffer to copy
             */
            ThreadSafeCircularBuffer(const ThreadSafeCircularBuffer &other);

            /*!
             * @brief dtor
             */
            ~ThreadSafeCircularBuffer() override = default;

            /*!
             * @brief Assignment operator
             * @param rhs the object to assign as
             * @return *this
             */
            ThreadSafeCircularBuffer &operator=(const ThreadSafeCircularBuffer &rhs);

            bool write(const void *data, size_t size) override;
            size_t read(void *toWrite, size_t size) override;
            size_t read(std::string &str, const char *delim, size_t size) override;
            void clear() override;
            bool isFull() const override;
            size_t getNbBufferedBytes() const override;
            size_t getBufferSize() const override;

        public:
            /*!
             * @brief Lock the internal mutex
             * Can be used to compute several interactions on the buffer without other threads modifying it in between
             * WARNING: don't forget to call unlock or the application will end in a deadlock.
             */
            void lock();
            /*!
             * @brief Unlock the internal mutex
             */
            void unlock();
            /*!
             * @brief try to lock the internal mutex by calling the try_lock function
             */
            void try_lock();

        private:
            mutable std::recursive_mutex _mutex; /*!< The mutex that is used to make the buffer thread safe */
        };
    }
}

#endif //B12NETWORKING_THREADSAFECIRCULARBUFFER_HPP
