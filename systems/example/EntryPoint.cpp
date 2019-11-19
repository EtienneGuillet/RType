#include "ExampleSystemApi.hpp"
#include <memory>

extern "C" {
    std::shared_ptr<ecs::ISystemAPI> entryPointSystemAPI() {
        return std::shared_ptr<ecs::ISystemAPI>(new ExampleSystemAPI());
    }
}