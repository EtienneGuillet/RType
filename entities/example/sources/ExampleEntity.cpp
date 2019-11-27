#include "ExampleEntity.hpp"
#include <components/IntComponent.hpp>
#include <components/CircleShapeComponent.hpp>

ExampleEntity::ExampleEntity()
    : Entity("ExampleEntity")
{
    addComponent(std::make_shared<rtype::CircleShapeComponent>());
}
