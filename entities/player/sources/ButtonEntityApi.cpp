#include "ButtonEntityApi.hpp"
#include "ButtonEntity.hpp"

const ecs::Version ButtonEntityAPI::Version = ecs::Version("Entity_Button", 1, 0, 0, 0);

const ecs::Version &ButtonEntityAPI::getVersion() const {
    return ButtonEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> ButtonEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new ButtonEntity());
}
