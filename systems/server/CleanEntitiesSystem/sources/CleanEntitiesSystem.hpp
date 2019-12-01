#ifndef R_TYPE_CleanEntitiesSystem_HPP
#define R_TYPE_CleanEntitiesSystem_HPP

#include "ecs/ASystem/ASystem.hpp"
#include "ecs/Version/Version.hpp"

class CleanEntitiesSystem : public ecs::ASystem {
public:
    CleanEntitiesSystem();
    virtual const ecs::Version &getType() const override;
    virtual void tick(long deltatime) override;

public:
    static const ecs::Version Version;
};


#endif //R_TYPE_CleanEntitiesSystem_HPP
