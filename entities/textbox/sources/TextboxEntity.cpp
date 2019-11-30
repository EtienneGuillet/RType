#include "TextboxEntity.hpp"
#include <components/TextComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/UpdateTextComponent.hpp>

TextboxEntity::TextboxEntity()
    : Entity("TextboxEntity")
{
    addComponent(std::make_shared<rtype::TextComponent>(1));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::UpdateTextComponent>());
}
