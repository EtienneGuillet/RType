#include "TitleSpriteEntityAPI.hpp"
#include "TitleSpriteEntity.hpp"

const ecs::Version TitleSpriteEntityAPI::Version = ecs::Version("Entity_TitleSprite", 0, 1, 0, 0);

const ecs::Version &TitleSpriteEntityAPI::getVersion() const {
    return TitleSpriteEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> TitleSpriteEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new TitleSpriteEntity());
}