#include "TextboxEntity.hpp"
#include <components/TextComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/UpdateTextComponent.hpp>
#include <components/HoverComponent.hpp>

TextboxEntity::TextboxEntity()
    : Entity("TextboxEntity")
{
    addComponent(std::make_shared<rtype::TextComponent>(1));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::UpdateTextComponent>());
    addComponent(std::make_shared<rtype::HoverComponent>());
}
