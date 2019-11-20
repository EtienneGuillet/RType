/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** testsAssertCriterionExist.cpp
*/

/* Created the 07/11/2019 at 18:06 by julian.frabel@epitech.eu */

#include <criterion/criterion.h>
#include "ecs/Version/Version.hpp"

static void init()
{}

static void fini()
{}

Test(test_version_operators, superior_true,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(true, max > min);
}

Test(test_version_operators, superior_false,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(false, min > max);
}

Test(test_version_operators, superior_invalid_type,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("tests", 1, 1, 1, 1);

    cr_assert_eq(false, max > min);
}

Test(test_version_operators, superior_equal_true,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(true, max >= min);
}

Test(test_version_operators, superior_equal_false,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(false, min >= max);
}

Test(test_version_operators, superior_equal_equal,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 1, 1, 1, 1);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(true, max >= min);
}

Test(test_version_operators, superior_equal_invalid_type,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("tests", 1, 1, 1, 1);

    cr_assert_eq(false, max >= min);
}

Test(test_version_operators, inferior_true,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(true, min < max);
}

Test(test_version_operators, inferior_false,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(false, max < min);
}

Test(test_version_operators, inferior_invalid_type,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("tests", 1, 1, 1, 1);

    cr_assert_eq(false, min < max);
}

Test(test_version_operators, inferior_equal_true,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(true, min <= max);
}

Test(test_version_operators, inferior_equal_false,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 1, 1, 1, 1);

    cr_assert_eq(false, max <= min);
}

Test(test_version_operators, inferior_equal_equal,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("test", 0, 0, 0, 0);

    cr_assert_eq(true, max <= min);
}

Test(test_version_operators, inferior_equal_invalid_type,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version min("test", 0, 0, 0, 0);
    ecs::Version max("tests", 1, 1, 1, 1);

    cr_assert_eq(false, min <= max);
}

Test(test_version_operators, equal_true,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    ecs::Version same("test", 1, 1, 1, 1);

    cr_assert_eq(true, version == same);
}

Test(test_version_operators, equal_false,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    ecs::Version same("test", 1, 1, 0, 1);

    cr_assert_eq(false, version == same);
}

Test(test_version_operators, equal_invalid_type,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    ecs::Version diff("tests", 1, 1, 1, 1);

    cr_assert_eq(false, version == diff);
}

Test(test_version_operators, not_equal_true,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    ecs::Version same("test", 0, 1, 1, 1);

    cr_assert_eq(true, version != same);
}

Test(test_version_operators, not_equal_false,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    ecs::Version same("test", 1, 1, 1, 1);

    cr_assert_eq(false, version != same);
}

Test(test_version_operators, not_equal_invalid_type,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    ecs::Version diff("tests", 1, 1, 1, 1);

    cr_assert_eq(true, version != diff);
}

Test(test_version_get_type, normal_string,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("test", 1, 1, 1, 1);
    std::string str("test");

    cr_assert_eq(true, version.getType() == str);
}

Test(test_version_get_type, empty_string,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("", 1, 1, 1, 1);
    std::string str("");

    cr_assert_eq(true, version.getType() == str);
}

Test(test_version_get_versions, valid_versions,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("", 1, 2, 3, 4);

    cr_assert_eq(true, version.getVersions()[0] == 1);
    cr_assert_eq(true, version.getVersions()[1] == 2);
    cr_assert_eq(true, version.getVersions()[2] == 3);
    cr_assert_eq(true, version.getVersions()[3] == 4);
}

Test(test_version_get_versions, valid_versions_no_argument,
    .timeout=10,
    .description="none",
    .init=init,
    .fini=fini
)
{
    ecs::Version version("");

    cr_assert_eq(true, version.getVersions()[0] == 0);
    cr_assert_eq(true, version.getVersions()[1] == 0);
    cr_assert_eq(true, version.getVersions()[2] == 0);
    cr_assert_eq(true, version.getVersions()[3] == 0);
}
