#include "LobbyContainerEntity.hpp"
#include <components/SpriteComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/ScrollComponent.hpp>

LobbyContainer::LobbyContainer()
    : Entity("LobbyContainer")
{
    addComponent(std::make_shared<rtype::SpriteComponent>(46));
    addComponent(std::make_shared<rtype::TransformComponent>());
    addComponent(std::make_shared<rtype::ScrollComponent>());
}
