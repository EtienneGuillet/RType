/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsAssertCriterionExist.cpp
*/

/* Created the 07/11/2019 at 18:06 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>

static void init()
{}

static void fini()
{}

Test(none, none,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    cr_assert(true);
}
