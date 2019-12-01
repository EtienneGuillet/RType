#include "LobbyContainerEntityApi.hpp"
#include "LobbyContainerEntity.hpp"

const ecs::Version LobbyContainerAPI::Version = ecs::Version("Entity_LobbyContainer", 1, 0, 0, 0);

const ecs::Version &LobbyContainerAPI::getVersion() const {
    return LobbyContainerAPI::Version;
}

std::shared_ptr<ecs::IEntity> LobbyContainerAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new LobbyContainer());
}
