/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** EntryPoint.cpp
*/

/* Created the 30/11/2019 at 12:49 by julian.frabel@epitech.eu */

#include "ClientGameNetworkEntitySyncSystemApi.hpp"
#include <memory>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define WIN_DLLEXPORT_COMPAT __declspec(dllexport)
#else
#define WIN_DLLEXPORT_COMPAT
#endif

extern "C" {
    WIN_DLLEXPORT_COMPAT ecs::ISystemAPI *entryPointSystemAPI() {
        return new rtype::ClientGameNetworkEntitySyncSystemApi();
    }
}