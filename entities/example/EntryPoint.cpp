#include "ecs/IEntityAPI/IEntityAPI.hpp"
#include "ExampleEntityApi.hpp"
#include <memory>

extern "C" {
    std::shared_ptr<ecs::IEntityAPI> entryPointEntityAPI() {
        return std::shared_ptr<ecs::IEntityAPI>(new ExampleEntityAPI());
    }
}