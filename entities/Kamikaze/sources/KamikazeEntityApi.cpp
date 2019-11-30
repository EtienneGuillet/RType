#include "KamikazeEntityApi.hpp"
#include "KamikazeEntity.hpp"

const ecs::Version KamikazeEntityAPI::Version = ecs::Version("Entity_Kamikaze", 1, 0, 0, 0);

const ecs::Version &KamikazeEntityAPI::getVersion() const {
    return KamikazeEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> KamikazeEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new KamikazeEntity);
}

long KamikazeEntityAPI::getSpawnFreq() const {
    return 1000 * 3;
}
