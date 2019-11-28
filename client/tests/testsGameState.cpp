/*
** EPITECH PROJECT, 2022
** testsGameState.cpp
** File description:
** Created by tpautier,
*/

#include <criterion/criterion.h>
#include "GameState.hpp"

Test(GameState, add_get_entity)
{
    rtype::GameState gameTest;
    rtype::EntitiesState entityTest;

    gameTest.addEntity(entityTest);
    rtype::EntitiesState entityCompare = gameTest.getEntity(0);

    cr_assert_eq(entityCompare.getId(), entityCompare.getId());
}

Test(GameState, remove_entity)
{
    rtype::GameState gameTest;
    rtype::EntitiesState entityTest;
    rtype::EntitiesState entityTest2;

    gameTest.addEntity(entityTest);
    gameTest.addEntity(entityTest2);

    cr_assert_eq(gameTest.getEntities().size(), 2);

    gameTest.removeEntity(0);

    cr_assert_eq(gameTest.getEntities().size(), 1);
}

Test(GameState, get_list_entities_by_ids)
{
    rtype::GameState gameTest;
    rtype::EntitiesState entityTest;
    rtype::EntitiesState entityTest2;
    rtype::EntitiesState entityTest3;

    entityTest.setId(1);
    entityTest2.setId(2);
    entityTest3.setId(3);
    gameTest.addEntity(entityTest);
    gameTest.addEntity(entityTest2);
    gameTest.addEntity(entityTest3);

    std::vector<std::uint32_t> ids = {1, 2};

    cr_assert_eq(gameTest.getEntities(ids).size(), 2);
}