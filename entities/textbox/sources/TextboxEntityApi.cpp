#include "TextboxEntityApi.hpp"
#include "TextboxEntity.hpp"

const ecs::Version TextboxEntityAPI::Version = ecs::Version("Entity_Textbox", 1, 0, 0, 0);

const ecs::Version &TextboxEntityAPI::getVersion() const {
    return TextboxEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> TextboxEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new TextboxEntity());
}
