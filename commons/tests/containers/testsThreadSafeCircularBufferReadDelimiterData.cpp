/*
** EPITECH PROJECT, 2019
** b12networking
** File description:
** testsThreadSafeCircularBufferReadDelimiterData.cpp
*/

/* Created the 28/10/2019 at 14:18 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "containers/ThreadSafeCircularBuffer.hpp"

static void init()
{}

static void fini()
{}

Test(threadsafecircularbuffer_read, read_delimiter_data,
     .timeout=10,
     .description="Test the reading with a delimiter from the thread safe buffer",
     .init=init,
     .fini=fini
)
{
    const char *expect = "blihblih\n\r";
    const char *write  = "blihblih\n\rbloh\n";
    int size = 15;
    b12software::containers::ThreadSafeCircularBuffer buffer(25);
    std::string str;

    buffer.write(write, size);
    size_t readed = buffer.read(str, "\n\r", 2);
    cr_assert_eq(readed, 10, "Expected to read %lu bytes but got %lu.", 10, readed);
    cr_assert_str_eq(str.c_str(), expect, "Expected [%s] but got [%s]", expect, str.c_str());
}