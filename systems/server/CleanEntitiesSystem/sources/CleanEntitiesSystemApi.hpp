#ifndef R_TYPE_CleanEntitiesSystemAPI_HPP
#define R_TYPE_CleanEntitiesSystemAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

class CleanEntitiesSystemAPI : public ecs::ISystemAPI {
public:
    [[nodiscard]] const ecs::Version &getVersion() const override;

    [[nodiscard]] std::shared_ptr<ecs::ISystem> createNewSystem() const override;

public:
    static const ecs::Version Version;
};


#endif //R_TYPE_CleanEntitiesSystemAPI_HPP
