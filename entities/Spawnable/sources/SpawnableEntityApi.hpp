#ifndef R_TYPE_SpawnableEntityAPI_HPP
#define R_TYPE_SpawnableEntityAPI_HPP


#include <ecs/IEntityAPI/ASpawnableEntityAPI.hpp>

class SpawnableEntityAPI : public ecs::ASpawnableEntityAPI {
public:
    const ecs::Version &getVersion() const override;

    std::shared_ptr<ecs::IEntity> createNewEntity() const override;

public:
    static const ecs::Version Version;
};


#endif //R_TYPE_SpawnableEntityAPI_HPP
