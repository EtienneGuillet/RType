/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** EntryPoint.cpp
*/

#include "EnemySpawnerApi.hpp"
#include <memory>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define WIN_DLLEXPORT_COMPAT __declspec(dllexport)
#else
#define WIN_DLLEXPORT_COMPAT
#endif

extern "C" {
    WIN_DLLEXPORT_COMPAT ecs::ISystemAPI *entryPointSystemAPI() {
        return new systems::EnemySpawnerApi();
    }
}