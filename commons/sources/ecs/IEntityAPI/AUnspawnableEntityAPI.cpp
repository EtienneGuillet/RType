//
// Created by Lilian on 29/11/2019.
//

#include "AUnspawnableEntityAPI.hpp"

bool ecs::AUnspawnableEntityAPI::isSpawnable() const {
    return false;
}

long ecs::AUnspawnableEntityAPI::getSpawnFreq() const {
    return 0;
}
