#include "ButtonEntity.hpp"
#include <components/SpriteComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TTLComponent.hpp>

ButtonEntity::ButtonEntity()
    : Entity("ButtonEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(42));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::TTLComponent>());
}
