#include "ButtonEntity.hpp"
#include <components/TextComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/HoverComponent.hpp>

ButtonEntity::ButtonEntity()
    : Entity("ButtonEntity")
{
    addComponent(std::make_shared<rtype::TextComponent>(1, "BUTTON"));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::HoverComponent>());
}
