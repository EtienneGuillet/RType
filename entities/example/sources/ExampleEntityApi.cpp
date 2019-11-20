#include "ExampleEntityApi.hpp"
#include "ExampleEntity.hpp"

const ecs::Version ExampleEntityAPI::Version = ecs::Version("Entity_Example", 1, 0, 0, 0);

const ecs::Version &ExampleEntityAPI::getVersion() const {
    return ExampleEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> ExampleEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new ExampleEntity);
}
