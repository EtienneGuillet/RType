#include "ExampleEntity.hpp"
#include <components/Int/IntComponent.hpp>

ExampleEntity::ExampleEntity() : Entity("ExampleEntity") {
    addComponent(std::make_shared<IntComponent>(0));
}