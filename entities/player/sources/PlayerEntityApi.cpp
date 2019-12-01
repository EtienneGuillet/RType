#include "PlayerEntityApi.hpp"
#include "PlayerEntity.hpp"

const ecs::Version PlayerEntityAPI::Version = ecs::Version("Entity_Player", 1, 0, 0, 0);

const ecs::Version &PlayerEntityAPI::getVersion() const {
    return PlayerEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> PlayerEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new PlayerEntity());
}
