#include "SpawnableEntityApi.hpp"
#include "SpawnableEntity.hpp"

const ecs::Version SpawnableEntityAPI::Version = ecs::Version("Entity_Spawnable", 1, 0, 0, 0);

const ecs::Version &SpawnableEntityAPI::getVersion() const {
    return SpawnableEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> SpawnableEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new SpawnableEntity);
}

long SpawnableEntityAPI::getSpawnFreq() const {
    return 1000 * 1;
}
