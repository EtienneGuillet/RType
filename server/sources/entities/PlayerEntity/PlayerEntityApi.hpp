#ifndef R_TYPE_PlayerEntityAPI_HPP
#define R_TYPE_PlayerEntityAPI_HPP


#include <ecs/IEntityAPI/AUnspawnableEntityAPI.hpp>

class PlayerEntityAPI : public ecs::AUnspawnableEntityAPI {
public:
    [[nodiscard]] const ecs::Version &getVersion() const override;

    [[nodiscard]] std::shared_ptr<ecs::IEntity> createNewEntity() const override;

public:
    static const ecs::Version Version;
};


#endif //R_TYPE_PlayerEntityAPI_HPP
