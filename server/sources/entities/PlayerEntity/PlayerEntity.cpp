#include "PlayerEntity.hpp"
#include <components/AIComponent/AIComponent.hpp>
#include <components/Transform/TransformComponent.hpp>
#include <logger/DefaultLogger.hpp>
#include <logger/StandardLogger.hpp>
#include <components/server/rigidbody/RigidbodyComponent.hpp>
#include <components/server/player/PlayerComponent.hpp>
#include <components/server/damageable/DamageableComponent.hpp>
#include <components/server/networkIdentity/NetworkIdentityComponent.hpp>
#include <components/server/weapon/WeaponComponent.hpp>
#include <components/server/collider/ColliderComponent.hpp>
#include <components/server/displayable/DisplayableComponent.hpp>

PlayerEntity::PlayerEntity(rtype::RTypeEntityType playerId) : Entity("PlayerEntity") {
    b12software::logger::DefaultLogger::SetDefaultLogger(std::make_shared<b12software::logger::StandardLogger>(b12software::logger::LogLevelDebug));

    addComponent(std::make_shared<ecs::components::DamageableComponent>(3, 3, 0, 0b1));
    addComponent(std::make_shared<ecs::components::TransformComponent>());
    addComponent(std::make_shared<ecs::components::WeaponComponent>(ecs::components::WeaponComponent::WEAPON_TYPE_STANDARD_WAVE_CANON, 500));
    addComponent(std::make_shared<ecs::components::ColliderComponent>());
    addComponent(std::make_shared<ecs::components::RigidbodyComponent>(15));
    addComponent(std::make_shared<ecs::components::PlayerComponent>());
    addComponent(std::make_shared<ecs::components::DisplayableComponent>(playerId));
}
