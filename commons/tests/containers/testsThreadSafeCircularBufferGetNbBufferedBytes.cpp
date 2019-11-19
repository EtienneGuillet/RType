/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** testsThreadSafeCircularBufferGetNbBufferedBytes.cpp
*/

/* Created the 28/10/2019 at 14:06 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "containers/ThreadSafeCircularBuffer.hpp"

static void init()
{}

static void fini()
{}

Test(threadsafecircularbuffer_get_nb_buffered_bytes, empty_buffer,
     .timeout=10,
     .description="Test the size taken of an empty thread safe buffer",
     .init=init,
     .fini=fini
)
{
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    cr_assert_eq(buffer.getNbBufferedBytes(), 0, "Expected buffered bytes to be 0 but was %lu", buffer.getNbBufferedBytes());
}

Test(threadsafecircularbuffer_get_nb_buffered_bytes, writen_buffer,
     .timeout=10,
     .description="Test the size taken of an writen thread safe buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[10] = {8};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 8);
    cr_assert_eq(buffer.getNbBufferedBytes(), 8, "Expected buffered bytes to be 8 after write but was %lu", buffer.getNbBufferedBytes());
}

Test(threadsafecircularbuffer_get_nb_buffered_bytes, readed_buffer,
     .timeout=10,
     .description="Test the size taken of an readed thread safe buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[10] = {8};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 8);
    buffer.read(to_write, 1);
    cr_assert_eq(buffer.getNbBufferedBytes(), 7, "Expected buffered bytes to be 7 after read but was %lu", buffer.getNbBufferedBytes());
}

Test(threadsafecircularbuffer_get_nb_buffered_bytes, odds_buffer_pointer_heads,
     .timeout=10,
     .description="Test the size taken of a thread safe buffer that have odds heads (read_idx = 7, write_idx = 1)",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[11] = {8};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 11);
    buffer.read(to_write, 6);
    cr_assert_eq(buffer.getNbBufferedBytes(), 4, "Expected buffered bytes to be 4 after read but was %lu", buffer.getNbBufferedBytes());
}

Test(threadsafecircularbuffer_get_nb_buffered_bytes, full_write_full_read,
     .timeout=10,
     .description="Test the size taken of a thread safe buffer that was full written then full readed",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[10] = {8};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 10);
    buffer.read(to_write, 10);
    cr_assert_eq(buffer.getNbBufferedBytes(), 0, "Expected buffered bytes to be 0 after read but was %lu", buffer.getNbBufferedBytes());
}