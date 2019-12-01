#include "ecs/IEntityAPI/IEntityAPI.hpp"
#include "KamikazeEntityApi.hpp"
#include <memory>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define WIN_DLLEXPORT_COMPAT __declspec(dllexport)
#else
#define WIN_DLLEXPORT_COMPAT
#endif

extern "C" {
	WIN_DLLEXPORT_COMPAT ecs::IEntityAPI *entryPointEntityAPI() {
        return new KamikazeEntityAPI();
    }
}