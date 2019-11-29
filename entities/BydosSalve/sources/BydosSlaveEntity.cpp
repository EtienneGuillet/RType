#include "BydosSlaveEntity.hpp"
#include <components/AIComponent/AIComponent.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/server/rigidbody/RigidbodyComponent.hpp>

BydosSlaveEntity::BydosSlaveEntity() : Entity("BydosSlaveEntity") {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    addComponent(std::make_shared<ecs::components::TransformComponent>());
    addComponent(std::make_shared<ecs::components::RigidbodyComponent>());
    addComponent(std::make_shared<ecs::components::AIComponent>([] (const std::shared_ptr<IEntity>& entity) {
        auto rb = std::dynamic_pointer_cast<ecs::components::RigidbodyComponent>(entity->getComponent(ecs::components::RigidbodyComponent::Version).lock());

        if (rb) {
            rb->setDirection(b12software::maths::Vector2D(10, 0));
            b12software::logger::DefaultLogger::Log(b12software::logger::LogLevelDebug, "AI " + entity->getName());
        }
    }));
}