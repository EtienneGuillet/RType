#include "BydosSlaveEntityApi.hpp"
#include "BydosSlaveEntity.hpp"

const ecs::Version BydosSlaveEntityAPI::Version = ecs::Version("Entity_Bydos_Slave", 1, 0, 0, 0);

const ecs::Version &BydosSlaveEntityAPI::getVersion() const {
    return BydosSlaveEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> BydosSlaveEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new BydosSlaveEntity);
}
