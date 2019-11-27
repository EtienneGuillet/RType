#include "PlayerEntity.hpp"
#include <components/SpriteComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TTLComponent.hpp>

PlayerEntity::PlayerEntity()
    : Entity("PlayerEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(42));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::TTLComponent>());
}
