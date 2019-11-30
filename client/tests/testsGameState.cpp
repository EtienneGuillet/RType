/*
** EPITECH PROJECT, 2022
** testsGameState.cpp
** File description:
** Created by tpautier,
*/

#include <criterion/criterion.h>
#include "rtype/client/NetworkState.hpp"

Test(GameState, add_get_entity)
{
    rtype::NetworkState gameTest;
    rtype::EntitiesState entityTest;

    gameTest.addEntity(entityTest);
    rtype::EntitiesState entityCompare = gameTest.getEntity(0);

    cr_assert_eq(entityCompare.getId(), entityCompare.getId());
}

Test(GameState, remove_entity)
{
    rtype::NetworkState gameTest;
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
    rtype::NetworkState gameTest;
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

Test(GameState, sort_by_z_index)
{
    rtype::NetworkState gameTest;
    rtype::EntitiesState entityTest;
    rtype::EntitiesState entityTest2;
    rtype::EntitiesState entityTest3;

    entityTest.setId(3);
    entityTest2.setId(1);
    entityTest3.setId(2);
    entityTest.setPos(0, 0, 69);
    entityTest2.setPos(0, 0, 21);
    entityTest3.setPos(0, 0, 42);
    gameTest.addEntity(entityTest);
    gameTest.addEntity(entityTest2);
    gameTest.addEntity(entityTest3);

    gameTest.sortByZindex();

    cr_assert_eq(gameTest.getEntities()[0].getId(), 1);
    cr_assert_eq(gameTest.getEntities()[1].getId(), 2);
    cr_assert_eq(gameTest.getEntities()[2].getId(), 3);
}