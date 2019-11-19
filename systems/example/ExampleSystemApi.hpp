#ifndef R_TYPE_EXAMPLESYSTEMAPI_HPP
#define R_TYPE_EXAMPLESYSTEMAPI_HPP

#include <ecs/ISystemAPI/ISystemAPI.hpp>

class ExampleSystemAPI : public ecs::ISystemAPI {
    [[nodiscard]] const ecs::Version &getVersion() const override;

    [[nodiscard]] std::shared_ptr<ecs::ISystem> createNewSystem() const override;

private:
    static const ecs::Version Version;
};


#endif //R_TYPE_EXAMPLESYSTEMAPI_HPP
