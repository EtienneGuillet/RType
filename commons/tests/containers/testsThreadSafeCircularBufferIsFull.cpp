/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** testsThreadSafeCircularBufferIsFull.cpp
*/

/* Created the 28/10/2019 at 14:16 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "containers/ThreadSafeCircularBuffer.hpp"

static void init()
{}

static void fini()
{}

Test(threadsafecircularbuffer_is_full, is_full_false,
     .timeout=10,
     .description="Test the is full function of a non full thread safe circular buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[6] = {6};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 6);
    cr_assert_eq(buffer.isFull(), false, "Expected isFull to return false but returned true");
}

Test(threadsafecircularbuffer_is_full, is_full_true,
     .timeout=10,
     .description="Test the is full function of a full thread safe circular buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[10] = {6};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 10);
    cr_assert_eq(buffer.isFull(), true, "Expected isFull to return true but returned false");
}

Test(threadsafecircularbuffer_is_full, is_full_after_overflow,
     .timeout=10,
     .description="Test the is full function of a full overflowed thread safe circular buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[11] = {6};
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 11);
    cr_assert_eq(buffer.isFull(), true, "Expected isFull to return true but returned false");
}

Test(threadsafecircularbuffer_is_full, is_full_after_reading,
     .timeout=10,
     .description="Test the is full function of a readen thread safe circular buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[10] = {6};
    std::uint8_t to_read[10];
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 10);
    cr_assert_eq(buffer.isFull(), true, "Expected isFull to return true but returned false");
    buffer.read(to_read, 1);
    cr_assert_eq(buffer.isFull(), false, "Expected isFull to return false but returned true");
}

Test(threadsafecircularbuffer_is_full, is_full_after_reading_overflow,
     .timeout=10,
     .description="Test the is full function of a readed overflowed thread safe circular buffer",
     .init=init,
     .fini=fini
)
{
    std::uint8_t to_write[11] = {6};
    std::uint8_t to_read[10];
    b12software::containers::ThreadSafeCircularBuffer buffer(10);

    buffer.write(to_write, 11);
    cr_assert_eq(buffer.isFull(), true, "Expected isFull to return true but returned false");
    buffer.read(to_read, 1);
    cr_assert_eq(buffer.isFull(), false, "Expected isFull to return false but returned true");
}