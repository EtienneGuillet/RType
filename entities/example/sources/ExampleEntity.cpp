#include "ExampleEntity.hpp"
#include <components/IntComponent.hpp>

ExampleEntity::ExampleEntity() : Entity("ExampleEntity") {
    addComponent(std::make_shared<rtype::IntComponent>(0));
}
