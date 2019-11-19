/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** ThreadSafeCircularBuffer.cpp
*/

/* Created the 28/10/2019 at 13:36 by julian.frabel@epitech.eu */

#include <cstring>
#include "containers/ThreadSafeCircularBuffer.hpp"

b12software::containers::ThreadSafeCircularBuffer::ThreadSafeCircularBuffer(int size)
    : CircularBuffer(size), _mutex()
{

}

b12software::containers::ThreadSafeCircularBuffer::ThreadSafeCircularBuffer(
    const b12software::containers::ThreadSafeCircularBuffer &other, const std::lock_guard<std::recursive_mutex> &)
    : CircularBuffer(other), _mutex()
{

}

b12software::containers::ThreadSafeCircularBuffer::ThreadSafeCircularBuffer(const b12software::containers::ThreadSafeCircularBuffer &other)
    : ThreadSafeCircularBuffer(other, std::lock_guard(other._mutex))
{

}

b12software::containers::ThreadSafeCircularBuffer &
b12software::containers::ThreadSafeCircularBuffer::operator=(const b12software::containers::ThreadSafeCircularBuffer &rhs)
{
    if (&rhs == this)
        return *this;
    std::scoped_lock lock(_mutex, rhs._mutex);
    CircularBuffer::operator=(rhs);
    return *this;
}

bool b12software::containers::ThreadSafeCircularBuffer::write(const void *data, size_t size)
{
    std::scoped_lock lock(_mutex);
    return CircularBuffer::write(data, size);
}

size_t b12software::containers::ThreadSafeCircularBuffer::read(void *toWrite, size_t size)
{
    std::scoped_lock lock(_mutex);
    return CircularBuffer::read(toWrite, size);
}

size_t b12software::containers::ThreadSafeCircularBuffer::read(std::string &str, const char *delim, size_t size)
{
    std::scoped_lock lock(_mutex);
    return CircularBuffer::read(str, delim, size);
}

void b12software::containers::ThreadSafeCircularBuffer::clear()
{
    std::scoped_lock lock(_mutex);
    CircularBuffer::clear();
}

bool b12software::containers::ThreadSafeCircularBuffer::isFull() const
{
    std::scoped_lock lock(_mutex);
    return CircularBuffer::isFull();
}

size_t b12software::containers::ThreadSafeCircularBuffer::getNbBufferedBytes() const
{
    std::scoped_lock lock(_mutex);
    return CircularBuffer::getNbBufferedBytes();
}

size_t b12software::containers::ThreadSafeCircularBuffer::getBufferSize() const
{
    std::scoped_lock lock(_mutex);
    return CircularBuffer::getBufferSize();
}

void b12software::containers::ThreadSafeCircularBuffer::lock()
{
    _mutex.lock();
}

void b12software::containers::ThreadSafeCircularBuffer::unlock()
{
    _mutex.unlock();
}

void b12software::containers::ThreadSafeCircularBuffer::tryLock()
{
    _mutex.try_lock();
}
