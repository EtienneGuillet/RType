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

Test(criterion, assert_criterion_exist,
    .timeout=10,
    .description="Assert that criterion exist",
    .init=init,
    .fini=fini
)
{
    cr_assert(true);
}
