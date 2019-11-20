#include <criterion/criterion.h>
#include "ecs/IDGenerator/IdGenerator.hpp"

static void init()
{}

static void fini()
{}

Test(IDGenerator, generateNewId,
     .timeout=10,
     .description="Test to generate new id",
     .init=init,
     .fini=fini
)
{
    ecs::IDGenerator generator;

    cr_assert_eq(generator.generateNewID(), 1);
}


Test(IDGenerator, generateTwoIds,
     .timeout=10,
     .description="Test to generate that don't collide",
     .init=init,
     .fini=fini
)
{
    ecs::IDGenerator generator;

    cr_assert_neq(generator.generateNewID(), generator.generateNewID());
}

Test(IDGenerator, freeAnId,
     .timeout=10,
     .description="Test to ensure that we can reuse freed ids",
     .init=init,
     .fini=fini
)
{
    ecs::IDGenerator generator;

    auto id1 = generator.generateNewID();

    generator.freeId(id1);
    cr_assert_eq(generator.generateNewID(), id1);
}

Test(IDGenerator, assignementOperator,
     .timeout=10,
     .description="Test to ensure that the operator = works",
     .init=init,
     .fini=fini
)
{
    ecs::IDGenerator generator;
    auto generator1 = generator;

    cr_assert_eq(generator.generateNewID(), generator1.generateNewID());
}

Test(IDGenerator, copyOperator,
     .timeout=10,
     .description="Test to ensure that the copy ctor works",
     .init=init,
     .fini=fini
)
{
    ecs::IDGenerator generator;
    ecs::IDGenerator generator1(generator);

    cr_assert_eq(generator.generateNewID(), generator1.generateNewID());
}
