/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** testsThreadSafeCircularBufferClear.cpp
*/

/* Created the 28/10/2019 at 14:04 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "containers/ThreadSafeCircularBuffer.hpp"

static void init()
{}

static void fini()
{}

Test(threadsafecircularbuffer_clear, clear_buffer,
     .timeout=10,
     .description="Test the clear function of a thread safe circular buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[10] = {10};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 10);
    buffer.clear();
    cr_assert_eq(buffer.getNbBufferedBytes(), 0, "Expected buffered bytes to be 0 after clear but was %lu", buffer.getNbBufferedBytes());
}