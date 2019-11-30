#include "TextInputEntity.hpp"

TextInputEntity::TextInputEntity()
: Entity("TextInputEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(45));
    addComponent(std::make_shared<rtype::TransformComponent>());
}