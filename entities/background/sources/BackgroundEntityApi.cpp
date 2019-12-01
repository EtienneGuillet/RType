#include "BackgroundEntityApi.hpp"
#include "BackgroundEntity.hpp"

const ecs::Version BackgroundEntityAPI::Version = ecs::Version("Entity_Background", 1, 0, 0, 0);

const ecs::Version &BackgroundEntityAPI::getVersion() const {
    return BackgroundEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> BackgroundEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new BackgroundEntity());
}
