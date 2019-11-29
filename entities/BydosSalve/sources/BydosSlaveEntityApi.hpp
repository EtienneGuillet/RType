#ifndef R_TYPE_BydosSlaveEntityAPI_HPP
#define R_TYPE_BydosSlaveEntityAPI_HPP


#include <ecs/IEntityAPI/ASpawnableEntityAPI.hpp>

class BydosSlaveEntityAPI : public ecs::ASpawnableEntityAPI {
public:
    [[nodiscard]] const ecs::Version &getVersion() const override;

    [[nodiscard]] std::shared_ptr<ecs::IEntity> createNewEntity() const override;

public:
    static const ecs::Version Version;
};


#endif //R_TYPE_BydosSlaveEntityAPI_HPP
