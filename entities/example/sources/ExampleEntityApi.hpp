#ifndef R_TYPE_EXAMPLEENTITYAPI_HPP
#define R_TYPE_EXAMPLEENTITYAPI_HPP


#include <ecs/IEntityAPI/IEntityAPI.hpp>

class ExampleEntityAPI : public ecs::IEntityAPI {
public:
    const ecs::Version &getVersion() const override;

    std::shared_ptr<ecs::IEntity> createNewEntity() const override;

public:
    static const ecs::Version Version;
};


#endif //R_TYPE_EXAMPLEENTITYAPI_HPP
