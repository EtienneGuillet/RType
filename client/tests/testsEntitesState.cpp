/*
** EPITECH PROJECT, 2022
** testsEntitesState.cpp
** File description:
** Created by tpautier,
*/

#include <criterion/criterion.h>
#include "rtype/client/EntitiesState.hpp"

Test(EntitiesState, create_entity)
{
    rtype::EntitiesState testEntity;
    b12software::maths::Vector3D posTest(0, 0, 0);
    b12software::maths::Vector2D rotTest(0, 0);
    b12software::maths::Vector2D scaleTest(1, 1);

    cr_assert_eq(testEntity.getId(), 0);
    cr_assert_eq(testEntity.getType(), 0);
    cr_assert_eq(testEntity.getPos(), posTest);
    cr_assert_eq(testEntity.getRot(), rotTest);
    cr_assert_eq(testEntity.getScale(), scaleTest);
}

Test(EntitiesState, setId)
{
    rtype::EntitiesState testEntity;

    testEntity.setId(42);
    cr_assert_eq(testEntity.getId(), 42);
}

Test(EntitiesState, setType)
{
    rtype::EntitiesState testEntity;

    testEntity.setType(42);
    cr_assert_eq(testEntity.getType(), 42);
}

Test(EntitiesState, setPos)
{
    b12software::maths::Vector3D posTest(42, 69, 21);
    rtype::EntitiesState testEntity;

    testEntity.setPos(42, 69, 21);
    cr_assert_eq(testEntity.getPos(), posTest);
}

Test(EntitiesState, setRot)
{
    b12software::maths::Vector2D rotTest(42, 69);
    rtype::EntitiesState testEntity;

    testEntity.setRot(42, 69);
    cr_assert_eq(testEntity.getRot(), rotTest);
}

Test(EntitiesState, setScale)
{
    b12software::maths::Vector2D scaleTest(42, 69);
    rtype::EntitiesState testEntity;

    testEntity.setScale(42, 69);
    cr_assert_eq(testEntity.getScale(), scaleTest);
}