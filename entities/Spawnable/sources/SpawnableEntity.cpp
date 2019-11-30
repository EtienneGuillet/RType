#include "SpawnableEntity.hpp"
#include <components/Int/IntComponent.hpp>

SpawnableEntity::SpawnableEntity() : Entity("SpawnableEntity") {
    addComponent(std::make_shared<IntComponent>(0));
}