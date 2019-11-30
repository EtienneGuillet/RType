#include "TextInputEntityApi.hpp"
#include "TextInputEntity.hpp"

const ecs::Version TextInputEntityAPI::Version = ecs::Version("Entity_textInput", 1, 0, 0, 0);

const ecs::Version &TextInputEntityAPI::getVersion() const {
    return TextInputEntityAPI::Version;
}

std::shared_ptr<ecs::IEntity> TextInputEntityAPI::createNewEntity() const {
    return std::shared_ptr<ecs::IEntity>(new TextInputEntity());
}
