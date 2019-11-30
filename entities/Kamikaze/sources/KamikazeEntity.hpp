#ifndef R_TYPE_KamikazeEntity_HPP
#define R_TYPE_KamikazeEntity_HPP

#include <ecs/IWorld/IWorld.hpp>
#include <maths/Vectors.hpp>
#include "ecs/IEntity/Entity.hpp"

class KamikazeEntity : public ecs::Entity {
public:
    KamikazeEntity();
private:
    std::vector<b12software::maths::Vector3D> getPlayerPositions(std::shared_ptr<ecs::IWorld> world);
};


#endif //R_TYPE_KamikazeEntity_HPP
