#ifndef R_TYPE_PlayerEntity_HPP
#define R_TYPE_PlayerEntity_HPP

#include <ecs/IWorld/IWorld.hpp>
#include <maths/Vectors.hpp>
#include <rtype/game/RTypeEntityType.hpp>
#include "ecs/IEntity/Entity.hpp"

class PlayerEntity : public ecs::Entity {
public:
    PlayerEntity(rtype::RTypeEntityType playerId);
};


#endif //R_TYPE_PlayerEntity_HPP
