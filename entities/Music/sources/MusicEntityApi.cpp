#include "MusicEntityApi.hpp"
#include "MusicEntity.hpp"

const ecs::Version MusicEntityAPI::Version = ecs::Version("Entity_Music", 1, 0, 0, 0);

const ecs::Version &MusicEntityAPI::getVersion() const {
    return MusicEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> MusicEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new MusicEntity());
}
