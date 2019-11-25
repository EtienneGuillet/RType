#include "ExampleEntity.hpp"
#include <components/IntComponent.hpp>
#include <components/SpriteComponent.hpp>

ExampleEntity::ExampleEntity()
    : Entity("ExampleEntity")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(1));
}
