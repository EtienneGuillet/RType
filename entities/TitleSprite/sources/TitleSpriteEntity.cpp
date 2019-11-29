#include "TitleSpriteEntity.hpp"
#include <components/SpriteComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TTLComponent.hpp>

TitleSpriteEntity::TitleSpriteEntity()
: Entity("TitleSpriteEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(44));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::TTLComponent>());
}