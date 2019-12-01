#include "MusicEntity.hpp"
#include <components/MusicComponent.hpp>

MusicEntity::MusicEntity()
    : Entity("MusicEntity")
{
    addComponent(std::make_shared<rtype::MusicComponent>());
}
