#include "BackgroundEntity.hpp"
#include <components/SpriteComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TTLComponent.hpp>

BackgroundEntity::BackgroundEntity()
    : Entity("BackgroundEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(43));
    addComponent(std::make_shared<rtype::TransformComponent>());
}
