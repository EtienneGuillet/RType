#ifndef R_TYPE_EXAMPLESYSTEM_HPP
#define R_TYPE_EXAMPLESYSTEM_HPP

#include "ecs/ASystem/ASystem.hpp"
#include "ecs/Version/Version.hpp"

class ExampleSystem : public ecs::ASystem {
    virtual const ecs::Version &getType() const override;
    virtual void tick(long deltatime) override;

private:
    static const ecs::Version Version;
};


#endif //R_TYPE_EXAMPLESYSTEM_HPP
