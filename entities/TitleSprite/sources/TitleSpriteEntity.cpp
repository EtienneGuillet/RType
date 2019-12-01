#include "TitleSpriteEntity.hpp"

TitleSpriteEntity::TitleSpriteEntity()
: Entity("TitleSpriteEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(44));
    addComponent(std::make_shared<rtype::TransformComponent>());
}