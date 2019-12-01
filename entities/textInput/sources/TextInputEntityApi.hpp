#ifndef _R_TYPE_BUTTON_ENTITY_API_HPP_
#define _R_TYPE_BUTTON_ENTITY_API_HPP_


#include <ecs/IEntityAPI/IEntityAPI.hpp>
#include <ecs/IEntityAPI/AUnspawnableEntityAPI.hpp>

class TextInputEntityAPI : public ecs::AUnspawnableEntityAPI {
public:
    const ecs::Version &getVersion() const override;

    std::shared_ptr<ecs::IEntity> createNewEntity() const override;

public:
    static const ecs::Version Version;
};


#endif //_R_TYPE_BUTTON_ENTITY_API_HPP_
