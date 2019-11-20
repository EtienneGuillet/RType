/*
** EPITECH PROJECT, 2022
** testASytem.cpp
** File description:
** testsASystem.cpp
*/

#include <criterion/criterion.h>
#include "ecs/ASystem/ASystem.hpp"

class TestASystem : public ecs::ASystem {

    public:

    TestASystem() = default;
    ~TestASystem() = default;

    void tick(long deltatime) override
    {
    }

    const ecs::Version &getType() const override
    {
        ecs::Version version("test");

        return version;
    }
};


static void init()
{}

static void fini()
{}

Test(ASystem, Asystem_create)
{
    TestASystem to_test;

    cr_assert_eq(to_test.isRunning(), false);
}

Test(ASystem, Asystem_start)
{
    TestASystem to_test;

    to_test.start();
    cr_assert_eq(to_test.isRunning(), true);
}

Test(ASystem, Asystem_stop)
{
    TestASystem to_test;

    to_test.start();
    to_test.stop();
    cr_assert_eq(to_test.isRunning(), false);
}
