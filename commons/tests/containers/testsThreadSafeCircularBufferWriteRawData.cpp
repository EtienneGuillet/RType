/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** testsThreadSafeCircularBufferWriteRawData.cpp
*/

/* Created the 28/10/2019 at 14:22 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "containers/ThreadSafeCircularBuffer.hpp"
#include "exception/NullPointerException.hpp"

static void init()
{}

static void fini()
{}

Test(threadsafecircularbuffer_write, raw_data,
     .timeout=10,
     .description="Test the write of raw data to the thread safe buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t data[6] = {0, 1, 2, 3, 4, 5};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    cr_assert_eq(buffer.write(data, sizeof(data)), false, "Buffer returned an overflow but wasn't expecting overflow");
}

Test(threadsafecircularbuffer_write, raw_data_fill_buffer,
     .timeout=10,
     .description="Test the write of raw data to the thread safe buffer and fill it without overflow",
     .init=init,
     .fini=fini
)
{
    std::uint8_t data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    cr_assert_eq(buffer.write(data, sizeof(data)), false, "Buffer returned an overflow when full but wasn't expecting overflow");
}

Test(threadsafecircularbuffer_write, raw_data_overflow_buffer,
     .timeout=10,
     .description="Test the write of raw data to the thread safe buffer and overflow it",
     .init=init,
     .fini=fini
)
{
    std::uint8_t data[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    cr_assert_eq(buffer.write(data, sizeof(data)), true, "Buffer did not return an overflow but was expecting one");
}

Test(threadsafecircularbuffer_write, null_data_pointer,
     .timeout=10,
     .description="Test the write of raw data to the thread safe buffer with a null pointer",
     .init=init,
     .fini=fini
)
{
    void *data = nullptr;
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    try {
        buffer.write(data, 1);
    } catch (b12software::exception::NullPointerException &e) {
        return;
    }
    cr_assert_fail("Was expecting a NullPointerException but got none");
}